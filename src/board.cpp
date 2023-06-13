#include "./board.hpp"

namespace chex {
  Board::Board() {
    for (auto& row : board) {
      for (auto& col : row) {
        col.state = CellState::EMPTY;
        col.piece = ChessPiece::NONE;
      }
    }
  }
}
