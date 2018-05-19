#pragma once

#include <vector>

enum Color
{
  BLACK, WHITE
};

enum Row
{
  ONE = 0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT
};

enum Col
{
  A = 0, B, C, D, E, F, G, H
};

class Position
{
public:
  Position(Col c, Row r) : col(c) , row(r) {}
  Col col;
  Row row;
};

class Piece
{

public:

  Piece(const Position& p, Color c) : pos(p) , color(c) {}

  Position get_position() const {return pos;}
  Color get_color() const {return color;}

  bool move_to(const Position& pos);

  virtual std::vector<Position> get_possible_move() const = 0;

  char type;

private:

  Position pos;
  Color color;
};
