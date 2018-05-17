#include "piece.hh"

enum class State
{
  CHECK,
  CHECKMATE,
  DRAW,
  TIMEOUT,
  RUNNING
};

class ChessBoard
{

public:

  ChessBoard();

  bool move(Position p1, Position p2);
  State get_state() const;

private:

  std::vector<Piece> pieces;
  State state;
  bool turn;
  bool rookw;
  bool rookb;
};
