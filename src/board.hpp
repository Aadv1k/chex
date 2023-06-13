#ifndef BOARD_HPP
#define BOARD_HPP

#include <stack>
#include <string>

namespace chex {

enum PieceType {
  WHITE_PAWN,
  WHITE_BISHOP,
  WHITE_KING,
  WHITE_QUEEN,
  WHITE_KNIGHT,
  WHITE_ROOK,

  BLACK_PAWN,
  BLACK_BISHOP,
  BLACK_KING,
  BLACK_QUEEN,
  BLACK_KNIGHT,
  BLACK_ROOK,
  NONE,
};

enum CellState { EMPTY, FILLED };

typedef struct {
  int x;
  int y;
} Vec2i;

typedef struct {
  PieceType type;
  Vec2i position;
} ChessPiece;

typedef struct {
  Vec2i from;
  Vec2i to;
  ChessPiece *capturedPiece;
  ChessPiece *currentPiece;
  bool isPromotion;
} ChessMove;

typedef struct {
  CellState state;
  ChessPiece *piece;
} Cell;

class Board {
  static const int boardSize = 8;
  Board();
  void initFromNotation(std::string notation);

private:
  Cell board[boardSize][boardSize];
};
} // namespace chex
#endif
