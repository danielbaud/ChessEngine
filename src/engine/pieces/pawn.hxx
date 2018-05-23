#include "pawn.hh"

std::vector<Position> Pawn::get_possible_move(ChessBoard *c) const
{
  std::vector<Position> p = std::vector<Position>();
  int col = 1;
  if (color == BLACK)
    col = -1;
  if (can_move_to(c, 0, col) == 0)
  {
    p.push_back(make_pos(0, col));
    if (((col == 1 && pos.row == TWO) || (col == -1 && pos.row == SEVEN))
          && can_move_to(c, 0, 2*col) == 0)
      p.push_back(make_pos(0, 2*col));
  }
  if (can_move_to(c, -1, col) == 1)
    p.push_back(make_pos(-1, col));
  if (can_move_to(c, 1, col) == 1)
    p.push_back(make_pos(1, col));
  return p;
}
