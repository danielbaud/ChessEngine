#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>

class Option
{

public:

  Option();

  bool parse(int argc, char **argv);
  bool get_help() const {return help;}
  int get_port() const {return port;}
  std::string get_pgn() const {return pgn_path;}
  std::vector<std::string> get_listeners() const {return listeners;}

private:

  bool help;
  int port;
  std::string pgn_path;
  std::vector<std::string> listeners;
};

#include "option.hxx"
