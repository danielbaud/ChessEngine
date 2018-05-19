#pragma once

#include "pieces/piece.hh"
#include "pieces/queen.hh"
#include "pieces/king.hh"
#include "pieces/bishop.hh"
#include "pieces/knight.hh"
#include "pieces/rook.hh"
#include "pieces/pawn.hh"


enum State
{
  CHECK, CHECKMATE, DRAW, TIMEOUT, RUNNING
};

class ChessBoard
{
public:

  ChessBoard();

  bool move(Position p1, Position p2);
  State get_state() const;

private:

  std::vector<Piece*> pieces;
  State state;
  Color turn;
  bool rookw;
  bool rookb;
};

#include "chessboard.hxx"
