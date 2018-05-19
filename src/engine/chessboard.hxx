#include "chessboard.hh"

const completed()
{
  std::vector<plugin::Rank> leter{A,B,C,D,E,F,G,H}
  std::vector<plugin::Rank> number{ONE,TWO,SEVEN,EIGHT}
  std::vector<PieceType> king{ROOK,KNIGHT,BISHOP,KING,QUEEN,BISHOP,KNIGHT,ROOK}
  std::vector<PieceType> queen{ROOK,KNIGHT,BISHOP,QUEEN,KING,BISHOP,KNIGHT,ROOK}
  Color c = Color::WHITE;
  for ( int n = 0 ; n < 4 ; n++)
  {
    if ( n > 2 )
      c = Color::BLACK
    for ( int i = 0 ; leter.size() ; i++ )
    { 
      if ( n == 1 || n == 2  )
        pieces.push_back(Piece(Position(leter[n], number[n]), plugin::PieceType::PAWN, c ));
      else
      {
        if ( n == 0 )
          pieces.push_back(Piece(Position(leter[n], number[n]), king[n], c ));
        else:
          pieces.push_back(Piece(Position(leter[n], number[n]), queen[n], c ));
      }
    }
  }
}


ChessBoard::ChessBoard()
{
  pieces = std::vector<Piece>();
  completed();
  state = State::RUNNING;
  turn = Color::WHITE;
  rookw = true;
  rookb = true;
}
