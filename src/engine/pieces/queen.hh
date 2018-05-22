#pragma once

#include "piece.hh"

class Queen : public Piece
{
public:

  Queen(const Position& p, Color c) : Piece(p, c) {type = 'Q';}

  std::vector<Position> get_possible_move(ChessBoard *c) const;
};

#include "queen.hxx"
