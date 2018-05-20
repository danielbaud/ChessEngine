#pragma once
#include <vector>
#include <string>

#include "../../plugin/listener.hh"
#include "../../plugin/chessboard-interface.hh"

namespace plugin
{

  class ListenerAdapter : public plugin::Listener
  {
  public:

    ListenerAdapter(std::vector<std::string> paths);
    ~ListenerAdapter();

    void register_board(const ChessboardInterface& board_interface);
    void on_game_started();
    void on_game_finished();
    void on_piece_moved(const PieceType piece,
                        const Position& from,
                        const Position& to);
    void on_piece_taken(const PieceType piece,
                        const Position& at);
    void on_piece_promoted(const PieceType piece,
                           const Position& at);
    void on_kingside_castling(const Color color);
    void on_queenside_castling(const Color color);
    void on_player_check(const Color color);
    void on_player_mat(const Color color);
    void on_player_pat(const Color color);
    void on_player_timeout(const Color color);
    void on_player_disqualified(const Color color);
    void on_draw();

  private:

    std::vector<Listener*> listeners;
    std::vector<void*> handlers;
  };
#include "listenerAdapter.hxx"
}
