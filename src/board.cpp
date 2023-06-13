#include "./board.hpp"
#include "../utils/utils.hpp"

namespace chex {

MoveValidity Board::isPawnMoveValid(ChessMove *move) {
  if (!isMoveWithinBounds(&move->to) || !isMoveWithinBounds(&move->from))
    return MoveValidity::OutOfBoundsMove;

  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  if (board[fromX][fromY].piece->type != move->currentPiece->type ||
      board[fromX][fromY].piece->color != move->currentPiece->color) {
    return MoveValidity::PieceMismatch;
  }

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

bool Board::isMoveWithinBounds(Vec2i *position) {
  const int size = boardSize;
  if (size <= position->x || size <= position->y)
    return false;

  if (position->x < 0 || position->y < 0)
    return false;

  return true;
}

} // namespace chex
