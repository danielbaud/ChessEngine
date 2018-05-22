#pragma once

#include "piece.hh"

class Bishop : public Piece
{
public:

  Bishop(const Position& p, Color c) : Piece(p, c) {type = 'B';}

  std::vector<Position> get_possible_move(ChessBoard *c) const;
};

#include "bishop.hxx"
