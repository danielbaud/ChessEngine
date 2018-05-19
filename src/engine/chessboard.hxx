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
