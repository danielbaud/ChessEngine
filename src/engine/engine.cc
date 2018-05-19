#include "engine.hh"
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
  if (opt.get_port() == -1 && opt.get_pgn() == "")
  {
    std::cerr << "No PGN file nor port given" << std::endl;
    return 0;
  }
  /* ----------------- */

  /* ENGINE */
  ChessBoard c = ChessBoard();
  return 0;
}
