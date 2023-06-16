#ifndef BOARD_HPP
#define BOARD_HPP

#include <cassert>
#include <iostream>
#include <stack>
#include <string>

namespace chex {

enum PieceType { PAWN, BISHOP, KING, QUEEN, KNIGHT, ROOK, NONE };

enum PieceColor { BLACK, WHITE, GREY };

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
} ChessMove;

typedef struct {
  CellState state;
  ChessPiece *piece;
} Cell;

class Board {
public:
  static const int boardSize = 8;
  Cell board[boardSize][boardSize];

  Board();
  ~Board();

  MoveValidity validateMove(ChessMove *move);
  ChessMove * makeMove(ChessMove *move);
  ChessMove * undoMove();
  PieceColor getCurrentPlayer();
  PieceColor setCurrentPlayer(PieceColor color);
  void print();
  void printColorMap();

private:
  std::stack<ChessMove *> undoStack;
  PieceColor currentPlayer;

  bool isMoveWithinBounds(ChessMove *move);
  void setCellToCell(Vec2i from, Vec2i to);
  MoveValidity isPawnMoveValid(ChessMove *move);
  MoveValidity isRookMoveValid(ChessMove *move);
  MoveValidity isBishopMoveValid(ChessMove *move);
  MoveValidity isKnightMoveValid(ChessMove *move);
  MoveValidity isQueenMoveValid(ChessMove *move);
  MoveValidity isKingMoveValid(ChessMove *move);
};

} // namespace chex

#endif
