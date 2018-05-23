#pragma once

#include "piece.hh"

class Rook : public Piece
{
public:

  Rook(const Position& p, Color c) : Piece(p, c) {type = 'R';}

  std::vector<Position> get_possible_move(ChessBoard *c, bool check) const;
};

#include "rook.hxx"
