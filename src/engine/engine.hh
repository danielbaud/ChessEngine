#pragma once

#include "adapters/listenerAdapter.hh"
#include "adapters/chessboardAdapter.hh"
#include "../network-api/server-network-api.hh"
#include "../network-api/common.hh"
#include <string>


class Player
{

public:

  Player(unsigned short port, bool col);
  void send(std::string msg);
  std::string receive();
  std::string receive_move();

  std::string login;
  Color color;

private:
  network_api::ServerNetworkAPI *net;
};

class Engine
{

public:

  Engine(unsigned short port, plugin::ListenerAdapter& lis);
  Engine(std::string pgn, plugin::ListenerAdapter& lis);

  bool move(Movement m);
  bool parse();
  bool start_game();
  void on_ending();

  Player *player1;
  Player *player2;

private:

  std::string pgn_path;
  plugin::ChessboardAdapter cbadapter;
  plugin::ListenerAdapter ladapter;

  Movement get_move(const std::string& line);
};

#include "engine.hxx"
