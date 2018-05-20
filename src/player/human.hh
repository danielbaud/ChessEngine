#pragma once

#include "player.hh"

class Human : public Player
{
public:

  Human(std::string ip, std::string port) : Player(ip, port) {}

  bool play();
};

#include "human.hxx"
