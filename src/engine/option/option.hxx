#include "option.hh"

Option::Option()
: help(false)
, port(-1)
, pgn_path("")
{
  listeners = std::vector<std::string>();
}

bool Option::parse(int argc, char **argv)
{
  int i = 1;
  while (i < argc)
  {
    if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
      help = true;
    else if (!strcmp(argv[i], "-p") || !(strcmp(argv[i], "--port")))
    {
      ++i;
      if (i == argc)
	return false;
      port = atoi(argv[i]);
    }
    else if (!strcmp(argv[i], "--pgn"))
    {
      ++i;
      if (i == argc)
	return false;
      pgn_path = std::string(argv[i]);
    }
    else if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "--listeners"))
    {
      ++i;
      if (i == argc)
	return false;
      while (i < argc && argv[i][0] != '-')
	listeners.push_back(std::string(argv[i++]));
      --i;
    }
    else
      return false;
    ++i;
  }
  return true;
}
