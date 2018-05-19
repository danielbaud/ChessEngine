#include "engine.hh"
#include <iostream>

Engine::Engine(unsigned short port)
: net(new network_api::ServerNetworkAPI(port))
{
  chessboard = ChessBoard();
}

Engine::Engine(std::string pgn)
{
  chessboard = ChessBoard();
  pgn_path = pgn;
}

bool Engine::move(Position p1, Position p2)
{
  (void)p1;
  (void)p2;
  return false;
}

bool Engine::parse()
{
  //parse pgn_path
  return false;
}

bool Engine::start_game()
{
  //uci protocol & play!
  return false;
}
