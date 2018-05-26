#include "ai.hh"

bool AI::play()
{
  srand(time(NULL));
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
    receive_move(receive());

  bool running = true;
  std::string comm;
  while (running)
  {
    comm = receive();
    if (comm == "quit")
      break;
    if (comm != "go")
      return false;

    std::string move = do_move();
    send("bestmove " + move);
    comm = receive();
    comm = receive_move(comm);
    running = (comm != "quit");
  }
  return true;
}

std::string AI::do_move()
{
  srand(time(NULL));

  std::string move = "";
  Color c = WHITE;
  Row r = EIGHT;
  if (color)
  {
    c = BLACK;
    r = ONE;
  }

  std::vector<Piece*> pieces = cb.get_pieces();

  std::vector<Piece*> my_pieces = std::vector<Piece*>();
  for (unsigned i = 0; i < pieces.size(); i++)
    if (pieces[i] && pieces[i]->get_color() == c)
      my_pieces.push_back(pieces[i]);

  std::vector<Movement> dest = std::vector<Movement>();
  for (unsigned i = 0; i < my_pieces.size(); ++i)
  {
    std::vector<Position> poss = my_pieces[i]->get_possible_move(&cb, true);
    for (unsigned j = 0; j < poss.size(); ++j)
    {
      if (my_pieces[i]->type == 'P' && poss[j].row == r)
        dest.push_back(Movement(my_pieces[i]->get_position(), poss[j], 'Q'));
      else
        dest.push_back(Movement(my_pieces[i]->get_position(), poss[j], 0));
    }
  }

  int m = rand() % dest.size();

  while (!cb.move(dest[m], 0, -1))
    m = rand() % dest.size();

  move += static_cast<int>(dest[m].from.col) + 'a';
  move += static_cast<int>(dest[m].from.row) + '1';

  move += static_cast<int>(dest[m].to.col) + 'a';
  move += static_cast<int>(dest[m].to.row) + '1';

  if (dest[m].promotion)
    move += dest[m].promotion;

  std::cout << "I did " << move << std::endl;
  return move;
}

std::string AI::receive_move(const std::string& log)
{
  if (log == "quit")
    return "quit";
  std::string ret = log.substr(log.size() - 5, log.size());
  if (ret.size() < 5)
    return " ";


  if (ret[0] == ' ')
    ret = ret.substr(1, ret.size());
  std::cout << "Opponent did " << ret << std::endl;

  Position from = Position(static_cast<Col>(ret[0] - 'a'),
                           static_cast<Row>(ret[1] - '1'));
  Position to = Position(static_cast<Col>(ret[2] - 'a'),
                         static_cast<Row>(ret[3] - '1'));
  char prom = 0;
  if (ret.size() == 5)
    prom = ret[4];

  Movement move = Movement(from, to, prom);
  cb.move(move, 0, -1);
  return ret;
}
