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


Engine::Engine(unsigned short port)
: player1(new Player(port, false)) , player2(new Player(port, true))
{
  chessboard = ChessBoard();
}

Engine::Engine(std::string pgn)
{
  chessboard = ChessBoard();
  pgn_path = pgn;
}

bool Engine::move(Movement m)
{
  if (m.from == m.to)
    return false;
  return true;
}

bool Engine::parse()
{
  //parse pgn_path
  return false;
}

bool Engine::start_game()
{
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

  /* GAME RUNNING */
  move1 = player1->receive_move();
  moves += " " + move1;
  if (!move(get_move(move1))) //DISQUALIFICATION
    return false;
  player2->send("ucinewgame");
  State game = chessboard.get_state();
  while (game == CHECK || game == RUNNING)
  {
    player2->send(moves);
    player2->send("go");
    move2 = player2->receive_move();
    moves += " " + move2;
    if (!move(get_move(move2)))
      return false;
    game = chessboard.get_state();
    if (game != CHECK && game != RUNNING)
      break;
    player1->send(moves);
    player1->send("go");
    move1 = player1->receive_move();
    moves += " " + move1;
    if (!move(get_move(move1)))
      return false;
    game = chessboard.get_state();
  }
  //Game FINISHED
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
