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
  std::vector<Position> poss = moved->get_possible_move(this, true);
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
  update_state();

  turn = turn == WHITE ? BLACK : WHITE;
  return true;
}

bool ChessBoard::is_check(Position p1, Position p2, Color c)
{
  int from = get_piece_index(p1);
  Piece *moved = pieces[from];
  if (from == -1)
    return false;
  int to = get_piece_index(p2);
  Piece *removed = nullptr;
  if (to > 0)
    removed = pieces[to];
  Piece *king = nullptr;
  for (unsigned i = 0; !king; ++i)
    if (pieces[i] && pieces[i]->get_color() == c && pieces[i]->type == 'K')
      king = pieces[i];
  if (removed)
    pieces[to] = nullptr;
  moved->move_to(p2);
  for (unsigned i = 0; i < pieces.size(); ++i)
  {
    if (pieces[i] && pieces[i]->get_color() != c)
    {
      std::vector<Position> poss = pieces[i]->get_possible_move(this, false);
      for (unsigned j = 0; j < poss.size(); ++j)
      {
	if (poss[j] == king->get_position())
	{
	  if (removed)
	    pieces[to] = removed;
	  moved->move_to(p1);
	  return true;
	}
      }
    }
  }
  if (removed)
    pieces[to] = removed;
  moved->move_to(p1);
  return false;
}

bool ChessBoard::is_check(Color c)
{
  Piece *king = nullptr;
  for (unsigned i = 0; !king; ++i)
    if (pieces[i] && pieces[i]->get_color() == c && pieces[i]->type == 'K')
      king = pieces[i];
  for (unsigned i = 0; i < pieces.size(); ++i)
  {
    if (pieces[i] && pieces[i]->get_color() != c)
    {
      std::vector<Position> poss = pieces[i]->get_possible_move(this, false);
      for (unsigned j = 0; j < poss.size(); ++j)
      {
        if (poss[j] == king->get_position())
  	  return true;
      }
    }
  }
  return false;
}

void ChessBoard::update_state()
{
  state = RUNNING;
  if (turn == WHITE)
  {
    if (is_check(BLACK))
      state = BLACK_CHECK;
  }
  else
  {
    if (is_check(WHITE))
      state = WHITE_CHECK;
  }
  bool can_move = false;
  for (unsigned i = 0; i < pieces.size(); ++i)
  {
    if (pieces[i] && pieces[i]->get_color() != turn)
    {
      std::vector<Position> p = pieces[i]->get_possible_move(this, true);
      if (p.size())
        can_move = true;
    }
  }
  if (!can_move)
  {
    if (state == BLACK_CHECK)
      state = BLACK_CHECKMATE;
    else if (state == WHITE_CHECK)
      state = WHITE_CHECKMATE;
    else
      state = DRAW;
  }
  if (state == BLACK_CHECK)
    ladapter.on_player_check(plugin::Color::BLACK);
  if (state == WHITE_CHECK)
    ladapter.on_player_check(plugin::Color::WHITE);
}
