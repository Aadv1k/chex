#ifndef BOARD_HPP
#define BOARD_HPP

namespace chex {
enum ChessPiece { PAWN, NONE };

enum CellState { EMPTY, FILLED };

typedef struct {
  CellState state;
  ChessPiece piece;
} Cell;

class Board {
  static const int boardSize = 8;
  Cell board[boardSize][boardSize];

  Board();
};
} // namespace chex
#endif
