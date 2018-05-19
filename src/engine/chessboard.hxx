#include "chessboard.hh"

ChessBoard::ChessBoard()
{
  pieces = std::vector<Piece>();
  pieces.push_back(Piece(Position(plugin::File::A, plugin::Rank::ONE), plugin::PieceType::ROOK, Color::WHITE));
  state = State::RUNNING;
  turn = Color::WHITE;
  rookw = true;
  rookb = true;
}


State ChessBoard::get_state() const { return state; }

std::optional<Piece> ChessBoard::get_piece(const Position& position)
{
  for (auto p : pieces)
  {
    if (p.get_position() == position)
      return p;
  }
  return std::nullopt;
}

std::optional<std::vector<Position>> ChessBoard::get_possible_move(const Position& position) const
{
  Piece p = get_piece(position);
  if (!p)
    return std::nullopt;
  std::vector<Position> positions = std::vector<Position>();
  return positions;
}
