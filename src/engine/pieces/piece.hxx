#include "piece.hh"


/**
 * Checks if a piece can move to a certain cell
 * return value:
 *   -2: cell is off board
 *   -1: cell is occupied by ally piece
 *    0: cell is empty
 *    1: cell is occupied by ennemy piece
**/
int Piece::can_move_to(ChessBoard *c, int col, int row) const
{
    int destc = static_cast<int>(pos.col) + col;
    int destr = static_cast<int>(pos.row) + row;
    if (destc < 0 || destc > 7 || destr < 0 || destr > 7)
      return -2;
    Position p = Position(static_cast<Col>(destc), static_cast<Row>(destr));
    int index = c->get_piece_index(p);
    if (index == -1)
      return 0;
    if (c->get_pieces()[index]->get_color() == color)
      return -1;
    return 1;
}

std::vector<Position> Piece::move_check(std::vector<Position> p, ChessBoard *c)
const
{
  std::vector<Position> res = std::vector<Position>();
  for (unsigned i = 0; i < p.size(); ++i)
    if (!c->is_check(pos, p[i], color))
      res.push_back(p[i]);
  return res;
}

bool Piece::is_passing(ChessBoard *c, int col, int row) const
{
    int destc = static_cast<int>(pos.col) + col;
    int destr = static_cast<int>(pos.row) + row;
    if (destc < 0 || destc > 7 || destr < 0 || destr > 7)
      return false;
    Position p = Position(static_cast<Col>(destc), static_cast<Row>(destr));
    int index = c->get_piece_index(p);
    if (index == -1)
      return false;
    if (c->get_pieces()[index]->passant)
      return true;
    return false;
}
