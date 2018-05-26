#pragma once

#include "adapters/listenerAdapter.hh"
#include "adapters/chessboardAdapter.hh"
#include "../network-api/server-network-api.hh"
#include "../network-api/common.hh"
#include <string>
#include <fstream>


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

  bool move(Movement m, char mov, int took);
  bool parse();
  bool start_game();
  void on_ending();

  Player *player1;
  Player *player2;

private:

  std::string pgn_path;
  plugin::ChessboardAdapter cbadapter;
  plugin::ListenerAdapter ladapter;
  bool is_end(std::string token);

  Movement get_move(const std::string& line);
  bool make_move(const std::string& line, Color color);
  void disqualify(plugin::Color color);
};

#include "engine.hxx"
