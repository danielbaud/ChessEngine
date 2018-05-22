#include "pawn.hh"

std::vector<Position> Pawn::get_possible_move(ChessBoard *c) const
{
  std::vector<Position> p = std::vector<Position>();
  if (can_move_to(c, 0, 1) == 0)
    p.push_back(make_pos(0, 1));
  if (can_move_to(c, -1, 1) == 1)
    p.push_back(make_pos(-1, 1));
  if (can_move_to(c, 1, 1) == 1)
    p.push_back(make_pos(1, 1));
  return p;
}
