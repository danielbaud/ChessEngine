#pragma once

#include <string>
#include "../network-api/client-network-api.hh"

class Player
{
public:

  Player(std::string ip, std::string port)
  : net(new network_api::ClientNetworkAPI(ip, port))
  {color = net->acknowledge("rivier_c");}

  bool get_color() const {return color;}
  void send(std::string line) {net->send(line);}
  std::string receive() {return net->receive();}
  virtual bool play() = 0;

protected:
  network_api::ClientNetworkAPI *net;
  bool color;
};
