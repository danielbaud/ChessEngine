#include "textListener.hh"
#include <iostream>
#include <string>

using namespace plugin;

void TextListener::register_board(const ChessboardInterface& board_interface)
{
  (void)board_interface;
}

void TextListener::on_game_started()
{
  std::cout << "Game has started" << std::endl;
}

void TextListener::on_game_finished()
{
  std::cout << "Game has ended" << std::endl;
}

void TextListener::on_piece_moved(const PieceType piece, const Position& from,
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
  std::cout << 'A' + static_cast<int>(from.file_get());
  std::cout << '1' + static_cast<int>(from.rank_get());
  std::cout << " to ";
  std::cout << 'A' + static_cast<int>(to.file_get());
  std::cout << '1' + static_cast<int>(to.rank_get()) << std::endl;
}

void TextListener::on_piece_taken(const PieceType piece, const Position& at)
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

void TextListener::on_piece_promoted(const PieceType piece, const Position& at)
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

void TextListener::on_kingside_castling(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "made a kingside castling" << std::endl;
}

void TextListener::on_queenside_castling(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "made a queenside castling" << std::endl;
}

void TextListener::on_player_check(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "is check" << std::endl;
}

void TextListener::on_player_mat(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "is checkmate" << std::endl;
}

void TextListener::on_player_pat(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "is pat" << std::endl;
}

void TextListener::on_player_timeout(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "has timed out" << std::endl;
}

void TextListener::on_player_disqualified(const Color color)
{
  if (color == Color::WHITE)
    std::cout << "White player ";
  else
    std::cout << "Black player ";
  std::cout << "is disqualified" << std::endl;
}

void TextListener::on_draw()
{
  std::cout << "Game is draw" << std::endl;
}

LISTENER_EXPORT(TextListener);
