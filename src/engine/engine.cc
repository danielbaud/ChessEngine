#include "engine.hh"
#include "adapters/listenerAdapter.hh"
#include "option/option.hh"
#include <iostream>

int main(int argc, char **argv)
{
  /* OPTION MANAGEMENT */
  Option opt;
  if (!opt.parse(argc, argv))
  {
    std::cerr << "Options given are not valid" << std::endl;
    return 0;
  }
  if (opt.get_help())
  {
    std::cerr << "Allowed options:" << std::endl;
    std::cerr << "\t-h [ --help ]\t\tshow usage" << std::endl;
    std::cerr << "\t-p [ --port ] arg\tselect the listening port" << std::endl;
    std::cerr << "\t--pgn arg\t\tpath to the PGN file" << std::endl;
    std::cerr << "\t-l [ --listeners ] args\tlist of the paths of the listeners plugins" << std::endl;
    return 0;
  }
  if (!opt.get_port() && opt.get_pgn() == "")
  {
    std::cerr << "No PGN file nor port given" << std::endl;
    return 0;
  }

  if (opt.get_port() && opt.get_pgn() != "")
  {
    std::cerr << "Both PGN file and port given" << std::endl;
    return 1;
  }

  /* ----------------- */

  /* LISTENERS */
  plugin::ListenerAdapter ladapter(opt.get_listeners());

  /* ----------------- */

  /* ENGINE */
  if (opt.get_port())
  {
    // SERVER ENGINE
    Engine engine(opt.get_port(), ladapter);
    if (!engine.start_game())
    {
      std::cerr << "Client bad protocol" << std::endl;
      return 1;
    }
    return 0;
  }
  //PGN ENGINE
  Engine engine(opt.get_pgn(), ladapter);
  if (!engine.parse())
    return 1;
  return 0;
}
