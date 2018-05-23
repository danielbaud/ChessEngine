#include "bishop.hh"

std::vector<Position> Bishop::get_possible_move(ChessBoard *c, bool check) const
{
  std::vector<Position> p = std::vector<Position>();
  int i = 1;
  while (can_move_to(c, i, i) == 0)
  {
    p.push_back(make_pos(i, i));
    ++i;
  }
  if (can_move_to(c, i, i) == 1)
    p.push_back(make_pos(i, i));
  i = 1;
  while (can_move_to(c, -i, i) == 0)
  {
    p.push_back(make_pos(-i, i));
    ++i;
  }
  if (can_move_to(c, -i, i) == 1)
    p.push_back(make_pos(-i, i));
  i = 1;
  while (can_move_to(c, i, -i) == 0)
  {
    p.push_back(make_pos(i, -i));
    ++i;
  }
  if (can_move_to(c, i, -i) == 1)
    p.push_back(make_pos(i, -i));
  i = 1;
  while (can_move_to(c, -i, -i) == 0)
  {
    p.push_back(make_pos(-i, -i));
    ++i;
  }
  if (can_move_to(c, -i, -i) == 1)
    p.push_back(make_pos(i, i));
  if (check)
    return move_check(p, c);
  return p;
}
