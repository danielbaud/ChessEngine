#pragma once

#include "piece.hh"

class Knight : public Piece
{
public:

  Knight(const Position& p, Color c) : Piece(p, c) {type = 'N';}

  std::vector<Position> get_possible_move(ChessBoard *c) const;
};

#include "knight.hxx"
