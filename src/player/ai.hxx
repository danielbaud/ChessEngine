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

  std::vector<int> co = cost(dest);
  int m = get_max_index(co);

  while (!cb.move(dest[m], 0, -1))
  {
    co[m] = -11;
    m = get_max_index(co);
  }

  move += static_cast<int>(dest[m].from.col) + 'a';
  move += static_cast<int>(dest[m].from.row) + '1';

  move += static_cast<int>(dest[m].to.col) + 'a';
  move += static_cast<int>(dest[m].to.row) + '1';

  if (dest[m].promotion)
    move += dest[m].promotion;

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

int AI::evaluate(char p)
{
  if (p == 'P')
    return 2;
  if (p == 'N' || p == 'B')
    return 6;
  if (p == 'R')
    return 10;
  if (p == 'Q')
    return 16;
  if (p == 'K')
    return 6;
  return 0;
}

std::vector<int> AI::cost(std::vector<Movement> moves)
{
  Color c = WHITE;
  Row r = ONE;
  if (!color)
  {
    c = BLACK;
    r = EIGHT;
  }
  std::vector<Piece*> pieces = cb.get_pieces();
  Piece* king = nullptr;
  for (unsigned i = 0; i < pieces.size(); ++i)
    if (pieces[i] && pieces[i]->type == 'K' && pieces[i]->get_color() == c)
      king = pieces[i];
  Position kpos = king->get_position();
  std::vector<int> ret = std::vector<int>();
  for (unsigned i = 0; i < moves.size(); ++i)
  {
    int check = 0;
    if (cb.is_check(moves[i].from, moves[i].to, c))
      check = 17;
    int from = cb.get_piece_index(moves[i].from);
    int to = cb.get_piece_index(moves[i].to);
    if (from == -1)
    {
      ret.push_back(-11);
      continue;
    }
    if (to == -1)
    {
      ret.push_back(check-evaluate(pieces[from]->type));
      continue;
    }
    check++;
    int dc = static_cast<int>(kpos.col) - static_cast<int>(moves[i].to.col);
    int dr = static_cast<int>(kpos.row) - static_cast<int>(moves[i].to.row);
    if (dc*dc <= 1 || dr*dr <= 1)
      check -= 14;
    if (pieces[from]->type == 'P' && moves[i].to.row == r)
      check += 20;
    ret.push_back(evaluate(pieces[to]->type)-evaluate(pieces[from]->type)+check);
  }
  return ret;
}

int AI::get_max_index(std::vector<int> v)
{
  srand(time(NULL));
  int max = -100;
  std::vector<int> res = std::vector<int>();
  for (unsigned i = 0; i < v.size(); ++i)
  {
    if (v[i] == max)
      res.push_back(i);
    if (v[i] > max)
    {
      res.clear();
      res.push_back(i);
      max = v[i];
    }
  }
  return res[rand() % res.size()];
}
