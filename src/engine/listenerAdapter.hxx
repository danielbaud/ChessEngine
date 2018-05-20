#include "listenerAdapter.hh"
#include <dlfcn.h>
#include <iostream>

ListenerAdapter::ListenerAdapter(std::vector<std::string> paths)
{
  listeners = std::vector<Listener*>();
  handlers = std::vector<void*>();
  for (unsigned i = 0; i < paths.size(); ++i)
  {
    void *handle = dlopen(paths[i].c_str(), RTLD_NOW);
    handlers.push_back(handle);
    void *symbol = dlsym(handle, "listener_create");
    listeners.push_back(reinterpret_cast<Listener*(*)()>(symbol)());
  }
}

ListenerAdapter::~ListenerAdapter()
{
  for (unsigned i = 0; i < handlers.size(); ++i)
    dlclose(handlers[i]);
}

void ListenerAdapter::register_board(const ChessboardInterface& board_interface)
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->register_board(board_interface);
}

void ListenerAdapter::on_game_started()
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_game_started();
}

void ListenerAdapter::on_game_finished()
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_game_finished();
}

void ListenerAdapter::on_piece_moved(const PieceType piece,
                                     const Position& from,
				     const Position& to)
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_piece_moved(piece, from, to);
}

void ListenerAdapter::on_piece_taken(const PieceType piece, const Position& at)
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_piece_taken(piece, at);
}

void ListenerAdapter::on_piece_promoted(const PieceType piece,
                                        const Position& at)
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_piece_promoted(piece, at);
}

void ListenerAdapter::on_kingside_castling(const Color color)
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_kingside_castling(color);
}

void ListenerAdapter::on_queenside_castling(const Color color)
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_queenside_castling(color);
}

void ListenerAdapter::on_player_check(const Color color)
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_player_check(color);
}

void ListenerAdapter::on_player_mat(const Color color)
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_player_mat(color);
}

void ListenerAdapter::on_player_pat(const Color color)
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_player_pat(color);
}

void ListenerAdapter::on_player_timeout(const Color color)
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_player_timeout(color);
}

void ListenerAdapter::on_player_disqualified(const Color color)
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_player_disqualified(color);
}

void ListenerAdapter::on_draw()
{
  for (unsigned i = 0; i < listeners.size(); ++i)
    listeners[i]->on_draw();
}
