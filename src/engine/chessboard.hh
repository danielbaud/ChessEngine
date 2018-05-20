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

class Movement
{
public:
  Movement(Position p1, Position p2, char prom)
  : from(p1) , to(p2) , promotion(prom) {}

  Position from;
  Position to;
  char promotion;
};

class ChessBoard
{
public:

  ChessBoard();

  bool move(Movement& m);
  State get_state() const {return state;}
  std::vector<Movement> get_possible_move() const;

private:

  std::vector<Piece*> pieces;
  State state;
  Color turn;
  bool rookw;
  bool rookb;
};

#include "chessboard.hxx"
