#pragma once

#include "piece.hh"

class Pawn : public Piece
{
public:

  Pawn(const Position& p, Color c) : Piece(p, c) {type = 'P';}

  std::vector<Position> get_possible_move(ChessBoard *c, bool check) const;
};

#include "pawn.hxx"
