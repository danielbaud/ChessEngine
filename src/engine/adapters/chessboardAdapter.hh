#pragma once

#include "../../plugin/chessboard-interface.hh"
#include "listenerAdapter.hh"
#include "../chessboard.hh"

namespace plugin
{

  class ChessboardAdapter : public ChessboardInterface
  {
  public:

    ChessboardAdapter(ListenerAdapter& lis)
    : chessboard(ChessBoard(lis)) , ladapter(lis)
    {}
    opt_piece_t operator[](const Position& position) const
    {
      opt_piece_t ret = std::nullopt;
      ::Col c = static_cast<::Col>(static_cast<int>(position.file_get()));
      ::Row r = static_cast<::Row>(static_cast<int>(position.rank_get()));
      ::Position p(c, r);
      std::vector<Piece*> pieces = chessboard.get_pieces();
      for (unsigned i = 0; i < pieces.size(); ++i)
      {
	if (pieces[i]->get_position() == p)
	{
	  ret = side_piece_t(static_cast<PieceType>(pieces[i]->type),
	                     pieces[i]->get_color() == WHITE?
			     Color::WHITE : Color::BLACK);
	}
      }
      return ret;
    }

    ChessBoard chessboard;

  private:

    ListenerAdapter ladapter;
  };
}
