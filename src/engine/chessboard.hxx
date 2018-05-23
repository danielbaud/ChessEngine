#include "chessboard.hh"

ChessBoard::ChessBoard(plugin::ListenerAdapter& lis)
: ladapter(lis)
{
  pieces = std::vector<Piece*>();
  state = RUNNING;
  turn = WHITE;
  rookw = true;
  rookb = true;
  pieces.push_back(new Rook(Position(A, ONE), WHITE));
  pieces.push_back(new Knight(Position(B, ONE), WHITE));
  pieces.push_back(new Bishop(Position(C, ONE), WHITE));
  pieces.push_back(new Queen(Position(D, ONE), WHITE));
  pieces.push_back(new King(Position(E, ONE), WHITE));
  pieces.push_back(new Bishop(Position(F, ONE), WHITE));
  pieces.push_back(new Knight(Position(G, ONE), WHITE));
  pieces.push_back(new Rook(Position(H, ONE), WHITE));
  pieces.push_back(new Pawn(Position(A, TWO), WHITE));
  pieces.push_back(new Pawn(Position(B, TWO), WHITE));
  pieces.push_back(new Pawn(Position(C, TWO), WHITE));
  pieces.push_back(new Pawn(Position(D, TWO), WHITE));
  pieces.push_back(new Pawn(Position(E, TWO), WHITE));
  pieces.push_back(new Pawn(Position(F, TWO), WHITE));
  pieces.push_back(new Pawn(Position(G, TWO), WHITE));
  pieces.push_back(new Pawn(Position(H, TWO), WHITE));
  pieces.push_back(new Rook(Position(A, EIGHT), BLACK));
  pieces.push_back(new Knight(Position(B, EIGHT), BLACK));
  pieces.push_back(new Bishop(Position(C, EIGHT), BLACK));
  pieces.push_back(new Queen(Position(D, EIGHT), BLACK));
  pieces.push_back(new King(Position(E, EIGHT), BLACK));
  pieces.push_back(new Bishop(Position(F, EIGHT), BLACK));
  pieces.push_back(new Knight(Position(G, EIGHT), BLACK));
  pieces.push_back(new Rook(Position(H, EIGHT), BLACK));
  pieces.push_back(new Pawn(Position(A, SEVEN), BLACK));
  pieces.push_back(new Pawn(Position(B, SEVEN), BLACK));
  pieces.push_back(new Pawn(Position(C, SEVEN), BLACK));
  pieces.push_back(new Pawn(Position(D, SEVEN), BLACK));
  pieces.push_back(new Pawn(Position(E, SEVEN), BLACK));
  pieces.push_back(new Pawn(Position(F, SEVEN), BLACK));
  pieces.push_back(new Pawn(Position(G, SEVEN), BLACK));
  pieces.push_back(new Pawn(Position(H, SEVEN), BLACK));
}

int ChessBoard::get_piece_index(const Position& p) const
{
  for (unsigned i = 0; i < pieces.size(); ++i)
    if (pieces[i] && pieces[i]->get_position() == p)
      return i;
  return -1;
}

bool ChessBoard::move(Movement& m)
{
  /* piece exists & is good color */
  int f = get_piece_index(m.from);
  Piece* moved = f == -1 ? nullptr : pieces[f];
  if (!moved || moved->get_color() != turn)
    return false;

  /* piece can move to destination */
  std::vector<Position> poss = moved->get_possible_move(this);
  bool goodmove = false;
  for (unsigned i = 0; i < poss.size(); ++i)
    if (poss[i] == m.to)
      goodmove = true;
  if (!goodmove)
    return false;

  /* if taken piece, removes it, else just move */
  int t = get_piece_index(m.to);
  Piece *taken = t == -1 ? nullptr : pieces[t];

  plugin::Position from = pieces[f]->get_plugin_position();
  pieces[f]->move_to(m.to);
  plugin::Position to = pieces[f]->get_plugin_position();
  if (taken)
  {
    pieces[t] = nullptr;
    ladapter.on_piece_moved(pieces[f]->get_plugin_piecetype(), from, to);
    ladapter.on_piece_taken(taken->get_plugin_piecetype(),
                            taken->get_plugin_position());
  }
  else
    ladapter.on_piece_moved(pieces[f]->get_plugin_piecetype(), from, to);

  turn = turn == WHITE ? BLACK : WHITE;
  return true;
}
