#include "rook.hh"

std::vector<Position> Rook::get_possible_move(ChessBoard *c, bool check) const
{
  std::vector<Position> p = std::vector<Position>();
  int i = 1;
  while (can_move_to(c, i, 0) == 0)
    p.push_back(make_pos(i++, 0));
  if (can_move_to(c, i, 0) == 1)
    p.push_back(make_pos(i, 0));
  i = -1;
  while (can_move_to(c, i, 0) == 0)
    p.push_back(make_pos(i--, 0));
  if (can_move_to(c, i, 0) == 1)
    p.push_back(make_pos(i, 0));
  i = 1;
  while (can_move_to(c, 0, i) == 0)
    p.push_back(make_pos(0, i++));
  if (can_move_to(c, 0, i) == 1)
    p.push_back(make_pos(0, i));
  i = -1;
  while (can_move_to(c, 0, i) == 0)
    p.push_back(make_pos(0, i--));
  if (can_move_to(c, 0, i) == 1)
    p.push_back(make_pos(0, i));
  if (check)
    return move_check(p, c);
  return p;
}
