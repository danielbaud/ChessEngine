#pragma once

#include "chessboard.hh"
#include "../network-api/server-network-api.hh"
#include "../network-api/common.hh"
#include <string>


class Engine
{

public:

  Engine(unsigned short port);
  Engine(std::string pgn);

  bool move(Position p1, Position p2);
  bool parse();
  bool start_game();

private:

  std::string pgn_path;
  ChessBoard chessboard;
  network_api::ServerNetworkAPI* net;
};

#include "engine.hxx"
