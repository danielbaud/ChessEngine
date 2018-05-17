#include "plugin/color.hh"
#include "plugin/piece-type.hh"
#include "plugin/position.hh"
#include <vector>

using Position = plugin::Position;
using Color = plugin::Color;
using PieceType = plugin::PieceType;

class Piece
{

public:

  Piece(Position p, PieceType t, Color c);

  Position get_position() const;
  PieceType get_type() const;
  std::vector<Position> get_possible_move() const;
  bool move_to(Position pos);

private:

  Position pos;
  PieceType type;
  Color col;
};
