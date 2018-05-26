#include "engine.hh"

Player::Player(unsigned short port, bool col)
: net(new network_api::ServerNetworkAPI(port))
{
  login = net->acknowledge(col);
  if (col)
    color = BLACK;
  else
    color = WHITE;
}

void Player::send(std::string msg)
{
  net->send(msg);
}
std::string Player::receive()
{
  return net->receive();
}

std::string Player::receive_move()
{
  std::string move = net->receive();
  if (move.substr(0, 9) != "bestmove " ||
     (move.size() != 13 && move.size() != 14))
    return "";
  return move.substr(9, 5);
}

/* -------------------------------------------------------------------------- */


Engine::Engine(unsigned short port, plugin::ListenerAdapter& lis)
: player1(new Player(port, false)) , player2(new Player(port, true))
, cbadapter(plugin::ChessboardAdapter(lis)) , ladapter(lis)
{}

Engine::Engine(std::string pgn, plugin::ListenerAdapter& lis)
: pgn_path(pgn) , cbadapter(plugin::ChessboardAdapter(lis)) , ladapter(lis)
{}

bool Engine::move(Movement m, char mov, int took)
{
  if (m.from == m.to)
    return false;
  return cbadapter.chessboard.move(m, mov, took);
}

bool Engine::parse()
{
  std::ifstream f(pgn_path);
  if (!f.is_open())
  {
    std::cerr << "Unable to find \"" << pgn_path << "\"" << std::endl;
    return false;
  }
  std::string temp;
  f >> temp;
  while (!f.eof() && temp != "1.")
    f >> temp;
  if (f.eof())
  {
    std::cerr << "Invalid PGN file \"" << pgn_path << "\"" << std::endl;
    return false;
  }

  State game = cbadapter.chessboard.get_state();
  ladapter.register_board(cbadapter);
  ladapter.on_game_started();

  while (!is_end(temp) && !cbadapter.chessboard.draw && (game == RUNNING ||
                               game == WHITE_CHECK || game == BLACK_CHECK))
  {
    f >> temp;
    if (!make_move(temp, WHITE))
    {
      disqualify(plugin::Color::WHITE);
      return true;
    }
    game = cbadapter.chessboard.get_state();
    if ((temp[temp.size()-1] == '+') != (game == BLACK_CHECK) ||
        (temp[temp.size()-1] == '#') != (game == BLACK_CHECKMATE))
    {
      disqualify(plugin::Color::WHITE);
      return true;
    }
    f >> temp;
    if (is_end(temp) || cbadapter.chessboard.draw || (game != RUNNING &&
                            game != WHITE_CHECK && game != BLACK_CHECK))
      break;
    if (!make_move(temp, BLACK))
    {
      disqualify(plugin::Color::BLACK);
      return true;
    }
    game = cbadapter.chessboard.get_state();
    if ((temp[temp.size()-1] == '+') != (game == WHITE_CHECK) ||
        (temp[temp.size()-1] == '#') != (game == WHITE_CHECKMATE))
    {
      disqualify(plugin::Color::BLACK);
      return true;
    }
    f >> temp;
  }
  if (temp == "1-0" && game == BLACK_CHECKMATE)
    ladapter.on_player_mat(plugin::Color::BLACK);
  if (temp == "0-1" && game == WHITE_CHECKMATE)
    ladapter.on_player_mat(plugin::Color::WHITE);
  if (temp == "1/2-1/2" && (cbadapter.chessboard.draw || game == WHITE_PAT
                            || game == BLACK_PAT))
  {
    if (game == WHITE_PAT)
      ladapter.on_player_pat(plugin::Color::WHITE);
    if (game == BLACK_PAT)
      ladapter.on_player_pat(plugin::Color::BLACK);
    ladapter.on_draw();
  }
  ladapter.on_game_finished();
  return true;
}

bool Engine::start_game()
{
  try
  {
    ladapter.register_board(cbadapter);
    std::string move1 = "";
    std::string move2 = "";
    std::string moves = "position startpos moves";
    /* starting game */
    player1->send("uci");
    if (player1->receive() != "uciok")
      return false;
    player2->send("uci");
    if (player2->receive() != "uciok")
      return false;
    player1->send("isready");
    if (player1->receive() != "readyok")
      return false;
    player2->send("isready");
    if (player2->receive() != "readyok")
      return false;
    player1->send("ucinewgame");
    player1->send("go");

    ladapter.on_game_started();
    /* GAME RUNNING */
    move1 = player1->receive_move();
    moves += " " + move1;
    if (!move(get_move(move1), 0, -1)) //DISQUALIFICATION
    {
      ladapter.on_player_disqualified(plugin::Color::WHITE);
      on_ending();
      return true;
    }
    player2->send("ucinewgame");
    State game = cbadapter.chessboard.get_state();
    while ((game == WHITE_CHECK || game == BLACK_CHECK || game == RUNNING)
            && !cbadapter.chessboard.draw)
    {
      player2->send(moves);
      player2->send("go");
      move2 = player2->receive_move();
      moves += " " + move2;
      if (!move(get_move(move2), 0, -1))
      {
        ladapter.on_player_disqualified(plugin::Color::BLACK);
        break;
      }
      game = cbadapter.chessboard.get_state();
      if ((game != BLACK_CHECK && game != WHITE_CHECK && game != RUNNING)
	   || cbadapter.chessboard.draw)
        break;
      player1->send(moves);
      player1->send("go");
      move1 = player1->receive_move();
      moves += " " + move1;
      if (!move(get_move(move1), 0, -1))
      {
        ladapter.on_player_disqualified(plugin::Color::WHITE);
        break;
      }
      game = cbadapter.chessboard.get_state();
    }
    if (game == WHITE_CHECKMATE)
      ladapter.on_player_mat(plugin::Color::WHITE);
    if (game == BLACK_CHECKMATE)
      ladapter.on_player_mat(plugin::Color::BLACK);
    if (cbadapter.chessboard.draw || game == WHITE_PAT || game == BLACK_PAT)
    {
      if (game == WHITE_PAT)
        ladapter.on_player_pat(plugin::Color::BLACK);
      if (game == BLACK_PAT)
        ladapter.on_player_pat(plugin::Color::WHITE);
      ladapter.on_draw();
    }
  }
  catch (const std::runtime_error& e)
  {
    plugin::Color pl = plugin::Color::WHITE;
    if (cbadapter.chessboard.get_turn() == BLACK)
      pl = plugin::Color::BLACK;
    ladapter.on_player_timeout(pl);
  }
  on_ending();
  return true;
}

Movement Engine::get_move(const std::string& line)
{
  Col clist[8] = {A, B, C, D, E, F, G, H};
  Row rlist[8] = {ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT};
  int fromc = line[0] - 'a';
  int fromr = line[1] - '1';
  int toc = line[2] - 'a';
  int tor = line[3] - '1';
  char prom = 0;
  if (line.size() == 5)
    prom = line[4];
  if (fromc > 7 || fromc < 0 || fromr > 7 || fromr < 0
      || toc > 7 || toc < 0 || tor > 7 || tor < 0)
    return Movement(Position(A,ONE), Position(A,ONE), prom);
  return Movement(Position(clist[fromc], rlist[fromr]),
                  Position(clist[toc], rlist[tor]), prom);
}

void Engine::on_ending()
{
  player1->send("quit");
  player2->send("quit");
  ladapter.on_game_finished();
}

bool Engine::is_end(std::string token)
{
  return token == "1-0" || token == "0-1" || token == "1/2-1/2" || token == "*";
}

bool Engine::make_move(const std::string& line, Color color)
{
  if (line == "O-O")
  {
    Row r = ONE;
    if (color == BLACK)
      r = EIGHT;
    return move(Movement(Position(E, r), Position(G, r), 0), 'K', 0);
  }
  if (line == "O-O-O")
  {
    Row r = ONE;
    if (color == BLACK)
      r = EIGHT;
    return move(Movement(Position(E, r), Position(C, r), 0), 'K', 0);
  }
  char prom = 0;
  int take = -1;
  if (line.size() < 5)
    return false;
  unsigned i = 0;
  char moved = 'P';
  if (line[i] < 'a')
  {
    moved = line[i];
    ++i;
  }
  int fc = line[i++] - 'a';
  int fr = line[i++] - '1';
  if (line[i] == '-')
    take = 0;
  else if (line[i] == 'x')
    take = 1;
  else
    return false;
  ++i;
  int tc = line[i++] - 'a';
  int tr = line[i++] - '1';
  if (fc > 7 || fc < 0 || fr > 7 || fr < 0 ||
      tc > 7 || tc < 0 || tr > 7 || tr < 0)
    return false;
  Position from = Position(static_cast<Col>(fc), static_cast<Row>(fr));
  Position to = Position(static_cast<Col>(tc), static_cast<Row>(tr));
  if (line.size() > i)
  {
    if (line[i] > 'A')
      prom = line[i++];
  }
  if (line.size() > i)
  {
    if (line[i] != '+' && line[i] != '#')
      return false;
    ++i;
  }
  if (line.size() != i)
    return false;
  return move(Movement(from, to, prom), moved, take);
}

void Engine::disqualify(plugin::Color color)
{
  ladapter.on_player_disqualified(color);
  ladapter.on_game_finished();
}
