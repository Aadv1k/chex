#ifndef BOARD_HPP
#define BOARD_HPP

#include <cassert>
#include <iostream>
#include <stack>
#include <string>

static constexpr int BOARD_SIZE = 8;

namespace chex {

enum PieceType { PAWN, BISHOP, KING, QUEEN, KNIGHT, ROOK, NONE };

enum PieceColor { BLACK, WHITE, GREY };

enum MoveValidity { OutOfBoundsMove, IllegalMove, PieceMismatch, LegalMove, Betrayal, BlockedPath };

enum CellState { EMPTY, FILLED };

struct Vec2i {
  int x;
  int y;
};

struct ChessPiece {
  PieceType type;
  PieceColor color;
  Vec2i position;
};

struct ChessMove {
  Vec2i from;
  Vec2i to;
};

struct Cell {
  CellState state;
  ChessPiece *piece;
};

class Board {
public:
  Cell board[BOARD_SIZE][BOARD_SIZE];

  Board();
  ~Board();

  MoveValidity validateMove(ChessMove *move) const;
  void makeMove(ChessMove *move);
  void undoMove();
  void print();
  void printColorMap();

private:
  std::stack<ChessMove *> undoStack;
  std::stack<ChessPiece *> capturedStack;

  PieceColor currentPlayer;

  bool isMoveWithinBounds(ChessMove *move) const;
  void setCellToCell(Vec2i from, Vec2i to);
  MoveValidity isPawnMoveValid(ChessMove *move) const;
  MoveValidity isRookMoveValid(ChessMove *move) const;
  MoveValidity isBishopMoveValid(ChessMove *move) const;
  MoveValidity isKnightMoveValid(ChessMove *move) const;
  MoveValidity isQueenMoveValid(ChessMove *move) const;
  MoveValidity isKingMoveValid(ChessMove *move) const;
};

} // namespace chex

#endif
