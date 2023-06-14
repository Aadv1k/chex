#include "./board.hpp"
#include "../utils/utils.hpp"

namespace chex {

MoveValidity Board::isPawnMoveValid(ChessMove *move) {
  if (!isMoveWithinBounds(move))
    return MoveValidity::OutOfBoundsMove;

  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  if (board[fromY][fromX].piece->type != move->currentPiece->type ||
      board[fromY][fromX].piece->color != move->currentPiece->color) {
    return MoveValidity::PieceMismatch;
  }

  if (board[toY][toX].piece->color == move->currentPiece->color)
    return MoveValidity::Betrayal

        switch (move->currentPiece->color) {
    case PieceColor::BLACK:
      if (toY - fromY != 1)
        return MoveValidity::IllegalMove;
      break;
    case PieceColor::WHITE:
      if (toY - fromY != -1)
        return MoveValidity::IllegalMove;
      break;
    }

  if (toX - fromX != -1 && toX - fromX != 1)
    return MoveValidity::IllegalMove;

  return MoveValidity::LegalMove;
}

MoveValidity Board::isRookMoveValid(ChessMove *move) {
  if (!isMoveWithinBounds(move))
    return MoveValidity::OutOfBoundsMove;

  const int[fromX, fromY] = move->from;
  const int[toX, toY] = move->to;

  auto b = Board::board;

  if (toY == fromY && fromX != toX)
    return MoveValidity::IllegalMove;

  if (move->currentPiece->color == move->capturedPiece->color) {
    return MoveValidity::Betrayal;
  }

  const int offset = toY > fromY ? 1 ? -1;
  int i = fromY;

  while () {
    if (i == toY)
      break;
    if (bp[i][fromX].state == CellState::FILLED)
      return MoveValidity::BlockedPath;
    i += offset
  }
  return MoveValidity::LegalMove;
}

Board::Board() {
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {

      ChessPiece piece = {
          .type = PieceType::NONE, .color = PieceColor::BLACK, .position = {.x = i, .y = j}};

      piece.color = (i == 0) ? PieceColor::BLACK : PieceColor::WHITE;

      if (i == 0 || i == boardSize - 1) {
        switch (j) {
        case boardSize - 0:
        case 0:
          piece.type = PieceType::ROOK;
          break;
        case boardSize - 1:
        case 1:
          piece.type = PieceType::KNIGHT;
          break;
        case boardSize - 2:
        case 2:
          piece.type = PieceType::BISHOP;
          break;
        case 3:
          piece.type = PieceType::QUEEN;
          break;
        case boardSize - 3:
          piece.type = PieceType::KING;
          break;
        }
      }

      board[i][j].state = (piece.type == PieceType::NONE) ? CellState::EMPTY : CellState::FILLED;
      board[i][j].piece = &piece;
    }
  }
}

bool Board::isMoveWithinBounds(ChessMove *move) {
  const int size = boardSize;

  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  if (size <= fromX || size <= fromY)
    return false;

  if (size <= toX || size <= toY)
    return false;

  if (position->x < 0 || position->y < 0)
    return false;

  return true;
}

} // namespace chex
