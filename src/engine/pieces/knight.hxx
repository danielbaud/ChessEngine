#include "knight.hh"

std::vector<Position> Knight::get_possible_move(ChessBoard *c) const
{
  std::vector<Position> p = std::vector<Position>();
  if (can_move_to(c, -1, 2) > -1)
    p.push_back(make_pos(-1,2));
  if (can_move_to(c, 1, 2) > -1)
    p.push_back(make_pos(1,2));
  if (can_move_to(c, 1, -2) > -1)
    p.push_back(make_pos(1,-2));
  if (can_move_to(c, -1, -2) > -1)
    p.push_back(make_pos(-1,-2));
  if (can_move_to(c, 2, 1) > -1)
    p.push_back(make_pos(2, 1));
  if (can_move_to(c, 2, -1) > -1)
    p.push_back(make_pos(2,-1));
  if (can_move_to(c, -2, 1) > -1)
    p.push_back(make_pos(-2,1));
  if (can_move_to(c, -2, -1) > -1)
    p.push_back(make_pos(-2,-1));
  return p;
}
