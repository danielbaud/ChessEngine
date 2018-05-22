#pragma once

#include "piece.hh"

class King : public Piece
{
public:

  King(const Position& p, Color c) : Piece(p, c) {type = 'K';}

  std::vector<Position> get_possible_move(ChessBoard *c) const;
};

#include "king.hxx"
