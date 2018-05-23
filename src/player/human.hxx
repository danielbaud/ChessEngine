#include "human.hh"

bool Human::play()
{
  std::string temp;
  if (receive() != "uci")
    return false;
  send("uciok");
  if (receive() != "isready")
    return false;
  send("readyok");
  if (receive() != "ucinewgame")
    return false;
  if (color)
    std::cout << receive() << std::endl;

  bool running = true;
  std::string comm;
  while (running)
  {
    comm = receive();
    if (comm == "quit")
      break;
    if (comm != "go")
      return false;
    std::cout << "What's your move? (lnln) : ";
    std::cin >> temp;
    send("bestmove " + temp);
    comm = receive();
    std::cout << comm << std::endl;
    running = (comm != "quit");
  }
  return true;
}
