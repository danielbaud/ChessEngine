#pragma once

#include "chessboard.hh"
#include "../network-api/server-network-api.hh"
#include "../network-api/common.hh"
#include <string>


class Engine
{

public:

  Engine(unsigned short port);

  bool move(Position p1, Position p2);
  bool parse(std::string path);
  bool start_game();

private:

  ChessBoard chessboard;
  network_api::ServerNetworkAPI net;
};
