#include "chessboard.hh"

ChessBoard::ChessBoard()
{
  pieces = new std::vector<Piece>();
  pieces.add(Piece(Position(A, ONE), ROOK, WHITE))
  state = RUNNING;
  turn = WHITE;
  rookw = true;
  rookb = true;
}
