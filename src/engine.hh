#pragma once

#include "chessboard.hh"
#include "chessboardAdapter.hh"
#include "listenerAdapter.hh"
#include "network-api/server-network-api.hh"
#include "network-api/common.hh"
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
  ChessboardAdapter cbadapter;
  ListenerAdapter ladapter;
  network_api::ServerNetworkAPI net;
};
