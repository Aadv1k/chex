#include "./board.hpp"

namespace chex {
Board::Board() {
  for (int i = 0; i < Board::boardSize; i++) {
    for (int j = 0; j < Board::boardSize; j++) {
      ChessPiece piece = {.type = PieceType::NONE, .position = {.x = i, .y = j}};

      Board::board[i][j].state = CellState::EMPTY;
      Board::board[i][j].piece = &piece;
    }
  }
}

void Board::initFromNotation(std::string notation) { /* TODO */}

} // namespace chex
