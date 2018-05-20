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
  while (true)
  {
    if (receive() != "go")
      return false;
    std::cout << "What's your move? (lnln) : ";
    std::cin >> temp;
    send("bestmove " + temp);
    std::cout << receive() << std::endl;
  }
  return true;
}
