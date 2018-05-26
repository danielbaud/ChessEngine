#include "player.hh"
#include "ai.hh"

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    std::cout << "Usage: " << argv[0] << " ip port" << std::endl;
    return 1;
  }
  std::vector<std::string> empty = std::vector<std::string>();
  plugin::ListenerAdapter ladapter = plugin::ListenerAdapter(empty);
  AI ai = AI(std::string(argv[1]), std::string(argv[2]), ladapter);
  std::cout << (ai.get_color()?"BLACK":"WHITE") << std::endl;
  if (!ai.play())
    return 1;
  return 0;
}
