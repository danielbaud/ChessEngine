#pragma once

#include <vector>
#include "../../plugin/chessboard-interface.hh"



class ChessBoard;

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

  bool operator==(Position p1) {return p1.col == this->col
                                    && p1.row == this->row;}
};

class Piece
{

public:

  Piece(const Position& p, Color c) : passant(false) , pos(p) , color(c) {}

  Position get_position() const {return pos;}
  Color get_color() const {return color;}

  plugin::Position get_plugin_position() const
  {
    return plugin::Position(static_cast<plugin::File>(static_cast<int>(pos.col))
                       , static_cast<plugin::Rank>(static_cast<int>(pos.row)));
  }

  plugin::Color get_plugin_color() const
  {
    if (color == WHITE)
      return plugin::Color::WHITE;
    return plugin::Color::BLACK;
  }

  plugin::PieceType get_plugin_piecetype() const
  {
    return static_cast<plugin::PieceType>(type);
  }

  int can_move_to(ChessBoard *c, int col, int row) const;

  Position make_pos(int col, int row) const
  {
    int posc = static_cast<int>(pos.col + col);
    int posr = static_cast<int>(pos.row + row);
    return Position(static_cast<Col>(posc), static_cast<Row>(posr));
  }

  std::vector<Position> move_check(std::vector<Position> p, ChessBoard *c) const;

  virtual void move_to(const Position& p) {pos = p;}

  virtual std::vector<Position> get_possible_move(ChessBoard *c, bool check) const = 0;

  bool is_passing(ChessBoard *c, int col, int row) const;

  bool can_castle(ChessBoard *c, bool kingside) const;

  char type;
  bool passant;

protected:
  Position pos;
  Color color;
};
