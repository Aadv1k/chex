#include "./board.hpp"
#include "../../utils/utils.hpp"

namespace chex {

// TODO: test pawn move validity checker
MoveValidity Board::isPawnMoveValid(ChessMove *move) {
  if (!isMoveWithinBounds(move))
    return MoveValidity::OutOfBoundsMove;

  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;
  const auto toPiece = board[toY][toX].piece;

  if (fromPiece->type != PieceType::PAWN) {
    return MoveValidity::PieceMismatch;
  }

  if (fromPiece->color == toPiece->color) {
    return MoveValidity::Betrayal;
  }

  switch (fromPiece->color) {
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

// TODO: test rook move validity checker
MoveValidity Board::isRookMoveValid(ChessMove *move) {
  if (!isMoveWithinBounds(move))
    return MoveValidity::OutOfBoundsMove;

  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;
  const auto toPiece = board[toY][toX].piece;

  if (fromPiece->color == toPiece->color) {
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

// TODO: test knight move validity checker
MoveValidity Board::isKnightMoveValid(ChessMove *move) {
  if (!isMoveWithinBounds(move))
    return MoveValidity::OutOfBoundsMove;

  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;
  const auto toPiece = board[toY][toX].piece;

  if (fromPiece->color == toPiece->color) {
    return MoveValidity::Betrayal;
  }

  const int diffX = fromX - toX;
  const int diffY = fromY - toY;

  if (!(diffX <= 3) || !(diffX <= 0 && diffX >= -3))
    return MoveValidity::IllegalMove;

  if (!(diffY <= 3) || !(diffY <= 0 && diffY >= -3))
    return MoveValidity::IllegalMove;

  return MoveValidity::LegalMove;
}

// TODO: test bishop move validity checker
MoveValidity Board::isBishopMoveValid(ChessMove *move) {
  if (!isMoveWithinBounds(move))
    return MoveValidity::OutOfBoundsMove;

  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;
  const auto toPiece = board[toY][toX].piece;

  if (fromPiece->color == toPiece->color) {
    return MoveValidity::Betrayal;
  }

  if (toX - fromX != fromX - toX)
    return MoveValidity::IllegalMove;

  const int offsetY = toY < fromY ? -1 : 1;
  const int offsetX = toX < fromX ? -1 : 1;
  auto const b = Board::board;

  for (int i = fromY, j = fromX; i != toY && j < toX; i += offsetY, j += offsetY) {
    if (b[i][i].state == CellState::FILLED) {
      return MoveValidity::BlockedPath;
    }
  }
  return MoveValidity::LegalMove;
}

MoveValidity Board::isQueenMoveValid(ChessMove *move) {
  const MoveValidity bishopMove = isBishopMoveValid(move);
  const MoveValidity pawnMove = isPawnMoveValid(move);
  const MoveValidity rookMove = isRookMoveValid(move);

  if (bishopMove != MoveValidity::LegalMove)
    return bishopMove;
  if (pawnMove != MoveValidity::LegalMove)
    return pawnMove;
  if (rookMove != MoveValidity::LegalMove)
    return rookMove;

  return MoveValidity::LegalMove;
}

MoveValidity Board::isKingMoveValid(ChessMove *move) {
  if (!isMoveWithinBounds(move))
    return MoveValidity::OutOfBoundsMove;

  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;
  const auto toPiece = board[toY][toX].piece;

  if (fromPiece->color == toPiece->color) {
    return MoveValidity::Betrayal;
  }

  const int diffX = toX - fromX;
  const int diffY = toY - fromY;

  if (!(diffX <= 1) || !(diffX >= -1))
    return MoveValidity::IllegalMove;

  if (!(diffY <= 1) || !(diffY >= -1))
    return MoveValidity::IllegalMove;

  return MoveValidity::LegalMove;
}

void Board::print() {
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
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

  PieceColor Board::getCurrentPlayer() {
    return currentPlayer;
  }

  PieceColor Board::setCurrentPlayer(PieceColor color) {
    currentPlayer = color;
    return getCurrentPlayer(); 
  }


Board::Board() {
  currentPlayer = PieceColor::WHITE;

  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      ChessPiece *piece = new ChessPiece{
          .type = PieceType::NONE, .color = PieceColor::BLACK, .position = {.x = i, .y = j}};

      piece->color = (i <= 1) ? PieceColor::BLACK : PieceColor::WHITE;

      if (i == 1 || i == boardSize - 2) {
        piece->type = PieceType::PAWN;
      }

      if (i == 0 || i == boardSize - 1) {
        switch (j) {
        case boardSize - 1:
        case 0:
          piece->type = PieceType::ROOK;
          break;
        case boardSize - 2:
        case 1:
          piece->type = PieceType::KNIGHT;
          break;
        case boardSize - 3:
        case 2:
          piece->type = PieceType::BISHOP;
          break;
        case 3:
          piece->type = PieceType::QUEEN;
          break;
        case boardSize - 4:
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
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      delete board[i][j].piece;
    }
  }
}

MoveValidity Board::validateMove(ChessMove *move) {

  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;

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
    assert(0 && "TODO: implement default state in validateMove");
    break;
  }
}

void Board::setCellToCell(Vec2i from, Vec2i to) {
  board[from.y][from.x] = board[to.y][to.x];

  board[from.y][from.x].state = CellState::EMPTY;
  board[from.y][from.x].piece = nullptr;
}

ChessMove * Board::makeMove(ChessMove *move) {
  auto toLocation = board[move->to.y][move->to.x];
  auto fromLocation = board[move->to.y][move->to.x];

  if (fromLocation.piece->color != getCurrentPlayer()) {
    assert(0 && "TODO: handle wrong player making the move");
  }



  if (MoveValidity::LegalMove != validateMove(move)) {
    assert(0 && "TODO: handle the NON legal move");
  }

  // This should not be triggered 
  // if (toLocation.piece->color == fromLocation.piece->color) {assert(0 && "TODO: handle friendly fire");}

  setCellToCell(move->from, move->to);
  undoStack.push(move);
  setCurrentPlayer(getCurrentPlayer() == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE);

  return move;
}

ChessMove * Board::undoMove() {
  if (undoStack.empty()) {
    assert(0 && "TODO: handle empty stack in undoMove");
  }
  ChessMove * ret = undoStack.top();
  setCellToCell(ret->to, ret->from);
  undoStack.pop();
  return ret;
}

bool Board::isMoveWithinBounds(ChessMove *move) {
  const int size = boardSize;

  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  if (size <= fromX || size <= fromY)
    return false;

  if (size <= toX || size <= toY)
    return false;

  return true;
}

} // namespace chex
