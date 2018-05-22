#include "rook.hh"

std::vector<Position> Rook::get_possible_move(ChessBoard *c) const
{
  std::vector<Position> p = std::vector<Position>();
  int i = 1;
  while (can_move_to(c, i, 0) > -1)
    p.push_back(make_pos(i++, 0));
  i = -1;
  while (can_move_to(c, i, 0) > -1)
    p.push_back(make_pos(i--, 0));
  i = 1;
  while (can_move_to(c, 0, i) > -1)
    p.push_back(make_pos(0, i++));
  i = -1;
  while (can_move_to(c, 0, i) > -1)
    p.push_back(make_pos(0, i--));
  return p;
}
