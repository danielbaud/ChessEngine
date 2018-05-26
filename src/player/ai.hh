#pragma once

#include "player.hh"
#include "../engine/chessboard.hh"
#include <ctime>

class AI : public Player
{
public:
  AI(std::string ip, std::string port, plugin::ListenerAdapter ladapter)
  : Player(ip, port) , cb(ChessBoard(ladapter)) {}

  bool play();
  std::string do_move();
  std::string receive_move(const std::string& log);

private:

  ChessBoard cb;
};

#include "ai.hxx"
