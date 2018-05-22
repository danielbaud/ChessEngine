#include "bishop.hh"

std::vector<Position> Bishop::get_possible_move(ChessBoard *c) const
{
  std::vector<Position> p = std::vector<Position>();
  for (int i = 1; can_move_to(c, i, i) >= 0; i++)
    p.push_back(make_pos(i, i));
  for (int i = 1; can_move_to(c, -i, i) >= 0; i++)
    p.push_back(make_pos(-i, i));
  for (int i = 1; can_move_to(c, i, -i) >= 0; i++)
    p.push_back(make_pos(i, -i));
  for (int i = 1; can_move_to(c, -i, -i) >= 0; i++)
    p.push_back(make_pos(-i, -i));
  return p;
}
