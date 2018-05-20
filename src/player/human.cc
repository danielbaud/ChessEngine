#include <iostream>
#include "player.hh"
#include "human.hh"

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    std::cout << "Usage: " << argv[0] << " ip port" << std::endl;
    return 1;
  }
  Human h = Human(std::string(argv[1]), std::string(argv[2]));
  std::cout << (h.get_color()?"BLACK":"WHITE") << std::endl;
  if (!h.play())
    return 1;
  return 0;
}
