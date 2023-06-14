#ifndef BOARD_HPP
#define BOARD_HPP

#include <stack>
#include <string>

namespace chex {

enum PieceType { PAWN, BISHOP, KING, QUEEN, KNIGHT, ROOK, NONE };

enum PieceColor { BLACK, WHITE };

enum MoveValidity { OutOfBoundsMove, IllegalMove, PieceMismatch, LegalMove, Betrayal, BlockedPath };

enum CellState { EMPTY, FILLED };

typedef struct {
  int x;
  int y;
} Vec2i;

typedef struct {
  PieceType type;
  PieceColor color;
  Vec2i position;
} ChessPiece;

typedef struct {
  Vec2i from;
  Vec2i to;
  ChessPiece *capturedPiece;
  ChessPiece *currentPiece;
  // bool isPromotion; // TODO: implement logic for piece promotion
} ChessMove;

typedef struct {
  CellState state;
  ChessPiece *piece;
} Cell;

class Board {
public:
  static const int boardSize = 8;
  Board();

  MoveValidity isPawnMoveValid(ChessMove *move);
  MoveValidity isRookMoveValid(ChessMove *move);
  MoveValidity isBishopMoveValid(ChessMove *move);
  MoveValidity isKnightMoveValid(ChessMove *move);

private:
  Cell board[boardSize][boardSize];
  bool isMoveWithinBounds(ChessMove *move);
};

} // namespace chex

#endif
