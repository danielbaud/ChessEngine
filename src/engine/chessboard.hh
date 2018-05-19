#pragma once

#include "piece.hh"
#include "../plugin/position.hh"
#include "../plugin/piece-type.hh"
#include "../plugin/color.hh"

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
  Color turn;
  bool rookw;
  bool rookb;
};

#include "chessboard.hxx"
