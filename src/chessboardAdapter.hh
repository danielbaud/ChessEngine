#include "plugin/chessboard-interface.hh"

class ChessboardAdapter : public plugin::ChessboardInterface
{

public:

  ChessboardAdapter();

  opt_piece_t operator[](const Position& position);
};
