#include "boardListener.hh"
#include <iostream>
#include <string>

using namespace plugin;

BoardListener::BoardListener() : cb(nullptr) {}

void BoardListener::register_board(const ChessboardInterface& board_interface)
{
  cb = &(board_interface);
}

void BoardListener::on_game_started()
{
  std::cout << "Game has started" << std::endl;
  print_board();
}

void BoardListener::on_game_finished()
{
  std::cout << "Game has ended" << std::endl;
}

void BoardListener::on_piece_moved(const PieceType piece, const Position& from,
                                  const Position& to)
{
  if (piece == PieceType::PAWN)
    std::cout << "Pawn ";
  else if (piece == PieceType::KING)
    std::cout << "King ";
  else if (piece == PieceType::QUEEN)
    std::cout << "Queen ";
  else if (piece == PieceType::BISHOP)
    std::cout << "Bishop ";
  else if (piece == PieceType::KNIGHT)
    std::cout << "Knight ";
  else if (piece == PieceType::ROOK)
    std::cout << "Rook ";
  std::cout << "moved from ";
  std::cout << static_cast<char>('A' + static_cast<int>(from.file_get()));
  std::cout << static_cast<char>('1' + static_cast<int>(from.rank_get()));
  std::cout << " to ";
  std::cout << static_cast<char>('A' + static_cast<int>(to.file_get()));
  std::cout << static_cast<char>('1' + static_cast<int>(to.rank_get())) << std::endl;
  print_board();
}

void BoardListener::on_piece_taken(const PieceType piece, const Position& at)
{
  if (piece == PieceType::PAWN)
    std::cout << "Pawn ";
  else if (piece == PieceType::KING)
    std::cout << "King ";
  else if (piece == PieceType::QUEEN)
    std::cout << "Queen ";
  else if (piece == PieceType::BISHOP)
    std::cout << "Bishop ";
  else if (piece == PieceType::KNIGHT)
    std::cout << "Knight ";
  else if (piece == PieceType::ROOK)
    std::cout << "Rook ";
  std::cout << "taken at ";
  std::cout << 'A' + static_cast<int>(at.file_get());
  std::cout << '1' + static_cast<int>(at.rank_get()) << std::endl;
}

void BoardListener::on_piece_promoted(const PieceType piece, const Position& at)
{
  if (piece == PieceType::QUEEN)
    std::cout << "Queen ";
  else if (piece == PieceType::BISHOP)
    std::cout << "Bishop ";
  else if (piece == PieceType::KNIGHT)
    std::cout << "Knight ";
  else if (piece == PieceType::ROOK)
    std::cout << "Rook ";
  std::cout << "promoted at ";
  std::cout << 'A' + static_cast<int>(at.file_get());
  std::cout << '1' + static_cast<int>(at.rank_get()) << std::endl;
}

void BoardListener::on_kingside_castling(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "made a kingside castling" << std::endl;
}

void BoardListener::on_queenside_castling(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "made a queenside castling" << std::endl;
}

void BoardListener::on_player_check(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "is check" << std::endl;
}

void BoardListener::on_player_mat(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "is checkmate" << std::endl;
}

void BoardListener::on_player_pat(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "is pat" << std::endl;
}

void BoardListener::on_player_timeout(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "has timed out" << std::endl;
}

void BoardListener::on_player_disqualified(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "is disqualified" << std::endl;
}

void BoardListener::on_draw()
{
  std::cout << "Game is draw" << std::endl;
}

void BoardListener::print_board()
{
  std::string blue("\x1b[2;34m");
  std::string white("\x1b[37m");
  std::string blackback("\x1b[40m");
  std::string grayback("\x1B[100m");
  for (int i = 7; i >= 0; --i)
  {
    std::cout << i+1 << "  ";
    for (int j = 0; j < 8; ++j)
    {
      if ((i+j) % 2 == 1)
	std::cout << grayback;
      else
	std::cout << blackback;
      Rank r = static_cast<Rank>(i);
      File f = static_cast<File>(j);
      std::optional<std::pair<PieceType, Color>> p = (*cb)[Position(f, r)];
      if (p == std::nullopt)
	std::cout << "   ";
      else
      {
	if ((*p).second == Color::BLACK)
	  std::cout << blue;
	else
	  std::cout << white;
	std::cout << " " << static_cast<char>((*p).first) << " ";
      }
    }
    std::cout << "\x1b[0m" <<  std::endl;
  }
  std::cout << std::endl  << "    A  B  C  D  E  F  G  H" << std::endl;
}

LISTENER_EXPORT(BoardListener);
