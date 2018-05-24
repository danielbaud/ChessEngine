#pragma once

#include "adapters/listenerAdapter.hh"
#include "pieces/piece.hh"
#include "pieces/queen.hh"
#include "pieces/king.hh"
#include "pieces/bishop.hh"
#include "pieces/knight.hh"
#include "pieces/rook.hh"
#include "pieces/pawn.hh"


enum State
{
  WHITE_CHECK, WHITE_CHECKMATE, BLACK_CHECK, BLACK_CHECKMATE,
  DRAW, TIMEOUT, RUNNING
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

  ChessBoard(plugin::ListenerAdapter& lis);

  bool move(Movement& m);
  State get_state() const {return state;}
  Color get_turn() const {return turn;}
  std::vector<Piece*> get_pieces() const {return pieces;}
  std::vector<Movement> get_possible_move() const;
  int get_piece_index(const Position& p) const;
  bool is_check(Position p1, Position p2, Color color);
  bool is_check(Color color);
  void manage_special(Movement& m);
  int castling(Piece *moved, Movement& m);
  void update_state();

  bool queenside_white;
  bool kingside_white;
  bool queenside_black;
  bool kingside_black;
  Color turn;
  plugin::ListenerAdapter ladapter;

private:

  std::vector<Piece*> pieces;
  State state;
};


#include "pieces/piece.hxx"
#include "chessboard.hxx"
