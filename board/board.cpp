#include "./board.hpp"
#include "../utils/utils.hpp"

namespace chex {

void Board::printColorMap() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      switch (board[i][j].piece->color) {
      case PieceColor::WHITE:
        std::cout << "W ";
        break;
      case PieceColor::BLACK:
        std::cout << "B ";
        break;
      case PieceColor::GREY:
        std::cout << "- ";
        break;
      }
    }
    std::cout << "\n";
  }
}

void Board::print() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j].state == CellState::FILLED) {
        const ChessPiece *piece = board[i][j].piece;
        std::string pieceSymbol;

        switch (piece->type) {
        case PieceType::PAWN:
          pieceSymbol = "p";
          break;
        case PieceType::BISHOP:
          pieceSymbol = "b";
          break;
        case PieceType::KING:
          pieceSymbol = "k";
          break;
        case PieceType::QUEEN:
          pieceSymbol = "q";
          break;
        case PieceType::KNIGHT:
          pieceSymbol = "n";
          break;
        case PieceType::ROOK:
          pieceSymbol = "r";
          break;
        default:
          pieceSymbol = "?";
          break;
        }

        if (piece->color == PieceColor::WHITE) {
          pieceSymbol[0] = std::toupper(pieceSymbol[0]);
        }

        std::cout << pieceSymbol << " ";
      } else {
        std::cout << "- ";
      }
    }
    std::cout << std::endl;
  }
}

Board::Board() {
  currentPlayer = PieceColor::WHITE;

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      ChessPiece *piece = new ChessPiece{
          .type = PieceType::NONE, .color = PieceColor::GREY, .position = {.x = i, .y = j}};

      if (i <= 1) {
        piece->color = PieceColor::BLACK;
      } else if (i >= 6) {
        piece->color = PieceColor::WHITE;
      }

      if (i == 1 || i == BOARD_SIZE - 2) {
        piece->type = PieceType::PAWN;
      }

      if (i == 0 || i == BOARD_SIZE - 1) {
        switch (j) {
        case BOARD_SIZE - 1:
        case 0:
          piece->type = PieceType::ROOK;
          break;
        case BOARD_SIZE - 2:
        case 1:
          piece->type = PieceType::KNIGHT;
          break;
        case BOARD_SIZE - 3:
        case 2:
          piece->type = PieceType::BISHOP;
          break;
        case 3:
          piece->type = PieceType::QUEEN;
          break;
        case BOARD_SIZE - 4:
          piece->type = PieceType::KING;
          break;
        }
      }

      board[i][j].state = (piece->type == PieceType::NONE) ? CellState::EMPTY : CellState::FILLED;
      board[i][j].piece = piece;
    }
  }
}

Board::~Board() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      delete board[i][j].piece;
    }
  }
}

bool Board::isMoveWithinBounds(ChessMove *move) const {
  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;
  const int size = BOARD_SIZE;

  if (fromX < 0 || fromX >= size || fromY < 0 || fromY >= size)
    return false;

  if (toX < 0 || toX >= size || toY < 0 || toY >= size)
    return false;

  return true;
}

MoveValidity Board::validateMove(ChessMove *move) const {
  const int fromX = move->from.x, fromY = move->from.y;

  if (!isMoveWithinBounds(move)) {
    return MoveValidity::IllegalMove;
  }

  const auto fromPiece = board[fromY][fromX].piece;

  if (fromPiece == NULL) {
    return MoveValidity::IllegalMove;
  }

  if (fromPiece->color != currentPlayer) {
    return MoveValidity::IllegalMove;
  }

  switch (fromPiece->type) {
  case PieceType::ROOK:
    return isRookMoveValid(move);
  case PieceType::BISHOP:
    return isBishopMoveValid(move);
  case PieceType::PAWN:
    return isPawnMoveValid(move);
  case PieceType::QUEEN:
    return isQueenMoveValid(move);
  case PieceType::KNIGHT:
    return isKnightMoveValid(move);
  case PieceType::KING:
    return isKingMoveValid(move);
  default:
    return MoveValidity::IllegalMove;
    break;
  }

  // this should not be reached
  return MoveValidity::IllegalMove;
}

void Board::makeMove(ChessMove *move) {
  if (!isMoveWithinBounds(move)) {
    assert(0 && "Move out of bounds");
  }

  auto fromLocation = board[move->from.y][move->from.x];
  auto toLocation = board[move->to.y][move->to.x];

  if (fromLocation.state == CellState::EMPTY) {
    assert(0 && "From target empty");
  }

  if (fromLocation.piece->color != currentPlayer) {
    assert(0 && "Wrong player making the move");
  }

  if (MoveValidity::LegalMove != validateMove(move)) {
    assert(0 && "Handle the NON legal move");
  }

  if (toLocation.state == CellState::FILLED) {
    capturedStack.push(toLocation.piece);
  }

  setCellToCell(move->from, move->to);
  undoStack.push(move);

  currentPlayer = currentPlayer == PieceColor::BLACK ? PieceColor::WHITE : PieceColor::BLACK;
}

void Board::undoMove() {
  if (undoStack.empty()) {
    assert(0 && "TODO: handle empty stack in undoMove");
  }
  ChessMove *lastMove = undoStack.top();

  Cell restoredCell;

  if (!capturedStack.empty()) {
    ChessPiece *lastCaptured = capturedStack.top();

    restoredCell = {.state = (lastCaptured->position.x == lastMove->to.x &&
                              lastCaptured->position.y == lastMove->to.y)
                                 ? CellState::FILLED
                                 : CellState::EMPTY,
                    .piece = lastCaptured};
  } else {
    restoredCell = {.state = CellState::EMPTY, .piece = nullptr};
  }

  board[lastMove->from.y][lastMove->from.x] = board[lastMove->to.y][lastMove->to.x];
  board[lastMove->to.y][lastMove->to.x] = restoredCell;

  undoStack.pop();
  capturedStack.pop();
}

void Board::setCellToCell(Vec2i from, Vec2i to) {
  board[to.y][to.x] = board[from.y][from.x];

  board[from.y][from.x].state = CellState::EMPTY;
  board[from.y][from.x].piece = nullptr;
}

MoveValidity Board::isPawnMoveValid(ChessMove *move) const {
  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;
  const auto toPiece = board[toY][toX].piece;

  const bool cellEmpty = board[toY][toX].state == CellState::EMPTY;

  if (!cellEmpty && toPiece->color == fromPiece->color) {
    return MoveValidity::PieceMismatch;
  }

  switch (fromPiece->color) {
  case PieceColor::WHITE:
    if (toY - fromY != -1)
      return MoveValidity::IllegalMove;
    break;
  case PieceColor::BLACK:
    if (toY - fromY != 1)
      return MoveValidity::IllegalMove;
    break;
  case PieceColor::GREY:
    assert(0 && "This should not happen");
    break;
  }

  if ((cellEmpty && toX - fromX == 1) || (cellEmpty && toX - fromX == -1))
    return MoveValidity::IllegalMove;

  return MoveValidity::LegalMove;
}

MoveValidity Board::isRookMoveValid(ChessMove *move) const {
  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;
  const auto toPiece = board[toY][toX].piece;

  if (toPiece && fromPiece->color == toPiece->color) {
    return MoveValidity::Betrayal;
  }

  if (toY == fromY && fromX != toX)
    return MoveValidity::IllegalMove;

  const int offset = toY > fromY ? 1 : -1;
  auto const b = Board::board;
  int i = fromY;

  while (1) {
    if (i == toY)
      break;
    if (b[i][fromX].state == CellState::FILLED)
      return MoveValidity::BlockedPath;
    i += offset;
  }
  return MoveValidity::LegalMove;
}

MoveValidity Board::isKnightMoveValid(ChessMove *move) const {
  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;
  const auto toPiece = board[toY][toX].piece;

  if (fromPiece->color == toPiece->color) {
    return MoveValidity::Betrayal;
  }

  const int diffX = abs(fromX - toX);
  const int diffY = abs(fromY - toY);

  if (diffX > 3 || diffY > 3) {
    return MoveValidity::IllegalMove;
  }

  return MoveValidity::LegalMove;
}

MoveValidity Board::isBishopMoveValid(ChessMove *move) const {
  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;
  const auto toPiece = board[toY][toX].piece;

  if (toPiece && fromPiece->color == toPiece->color) {
    return MoveValidity::Betrayal;
  }

  const int diffX = toX - fromX;
  const int diffY = toY - fromY;

  if (abs(diffX) != abs(diffY))
    return MoveValidity::IllegalMove;

  const int offsetX = (diffX > 0) ? 1 : -1;
  const int offsetY = (diffY > 0) ? 1 : -1;

  int i = fromY + offsetY;
  int j = fromX + offsetX;

  while (i != toY && j != toX) {
    if (board[i][j].state == CellState::FILLED) {
      return MoveValidity::BlockedPath;
    }
    i += offsetY;
    j += offsetX;
  }

  return MoveValidity::LegalMove;
}

MoveValidity Board::isQueenMoveValid(ChessMove *move) const {

  const MoveValidity pawnMove = isPawnMoveValid(move);
  const MoveValidity rookMove = isRookMoveValid(move);
  const MoveValidity bishopMove = isBishopMoveValid(move);

  if ((pawnMove == MoveValidity::LegalMove) || (bishopMove == MoveValidity::LegalMove) ||
      (rookMove == MoveValidity::LegalMove))
    return MoveValidity::LegalMove;

  return MoveValidity::IllegalMove;
}

MoveValidity Board::isKingMoveValid(ChessMove *move) const {
  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;
  const auto toPiece = board[toY][toX].piece;

  if (toPiece && fromPiece->color == toPiece->color) {
    return MoveValidity::Betrayal;
  }

  const int diffX = abs(toX - fromX);
  const int diffY = abs(toY - fromY);

  if (diffX > 1 || diffY > 1) {
    return MoveValidity::IllegalMove;
  }
  return MoveValidity::LegalMove;
}

} // namespace chex
