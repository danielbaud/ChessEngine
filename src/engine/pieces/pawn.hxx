#include "pawn.hh"

std::vector<Position> Pawn::get_possible_move(ChessBoard *c, bool check) const
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
  if (can_move_to(c, -1, col) == 1 || is_passing(c, -1, 0))
    p.push_back(make_pos(-1, col));
  if (can_move_to(c, 1, col) == 1 || is_passing(c, 1, 0))
    p.push_back(make_pos(1, col));
  if (check)
    return move_check(p, c);
  return p;
}

void Pawn::move_to(const Position& p)
{
  Row fr = TWO;
  Row tr = FOUR;
  if (color == BLACK)
  {
    fr = SEVEN;
    tr = FIVE;
  }
  if (pos.row == fr && p.row == tr)
    passant = true;
  else
    passant = false;
  pos = p;
}
