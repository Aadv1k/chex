#include "./board.hpp"
#include "../utils/utils.hpp"

namespace chex {

// TODO: test pawn move validity checker
MoveValidity Board::isPawnMoveValid(ChessMove *move) {
  if (!isMoveWithinBounds(move))
    return MoveValidity::OutOfBoundsMove;

  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  const auto fromPiece = board[fromY][fromX].piece;

  if (fromPiece->type != PieceType::PAWN) {
    return MoveValidity::PieceMismatch;
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
  case PieceColor::GREY:
    assert(0 && "something wrong here");
    break;
  }

  if (toX - fromX <= -1)
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

  const int diffX = abs(fromX - toX);
  const int diffY = abs(fromY - toY);

  if (diffX > 3 || diffY > 3) {
    return MoveValidity::IllegalMove;
  }

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

  PieceColor Board::getCurrentPlayer() {
    return currentPlayer;
  }



Board::Board() {
  currentPlayer = PieceColor::WHITE;

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      ChessPiece *piece = new ChessPiece{
          .type = PieceType::NONE,
          .color = PieceColor::GREY,
          .position = {.x = i, .y = j}
      };

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

MoveValidity Board::validateMove(ChessMove *move) {
  const int fromX = move->from.x, fromY = move->from.y;
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

  // this should not be reached
  return MoveValidity::IllegalMove;
}

void Board::setCellToCell(Vec2i from, Vec2i to) {
  board[to.y][to.x] = board[from.y][from.x];

  board[from.y][from.x].state = CellState::EMPTY;
  board[from.y][from.x].piece = nullptr;
}

ChessMove * Board::makeMove(ChessMove *move) {
  auto fromLocation = board[move->from.y][move->from.x];
  auto toLocation = board[move->to.y][move->to.x];

  if (fromLocation.state == CellState::EMPTY) {
    assert(0 && "TODO: EMPTY location");
  }

  if (fromLocation.piece->color != currentPlayer) {
    assert(0 && "TODO: handle wrong player making the move");
  }

  if (MoveValidity::LegalMove != validateMove(move)) {
    assert(0 && "TODO: handle the NON legal move");
  }

  if (toLocation.state == CellState::FILLED) {
    capturedStack.push(toLocation.piece);
  }


  toLocation.piece->position = move->to;

  setCellToCell(move->from, move->to);
  undoStack.push(move);

  currentPlayer = currentPlayer == PieceColor::BLACK ? PieceColor::WHITE : PieceColor::BLACK;

  return move;
}

ChessMove * Board::undoMove() {
  if (undoStack.empty()) {
    assert(0 && "TODO: handle empty stack in undoMove");
    return nullptr;
  }

  ChessMove * lastMove = undoStack.top();
  ChessPiece * lastCaptured = capturedStack.top();


  

  Cell restoredCell = {
    .state = (
              lastCaptured->position.x == lastMove->to.x &&
              lastCaptured->position.y == lastMove->to.y
              ) ? CellState::FILLED : CellState::EMPTY,
    .piece = lastCaptured
  };

  board[lastMove->from.y][lastMove->from.x] = board[lastMove->to.y][lastMove->to.x];
  board[lastMove->to.y][lastMove->to.x] = restoredCell;



  undoStack.pop();
  capturedStack.pop();
  return lastMove;
}

bool Board::isMoveWithinBounds(ChessMove *move) {
  const int fromX = move->from.x, fromY = move->from.y;
  const int toX = move->to.x, toY = move->to.y;

  if (BOARD_SIZE <= fromX || BOARD_SIZE <= fromY)
    return false;

  if (BOARD_SIZE <= toX || BOARD_SIZE <= toY)
    return false;

  return true;
}

} // namespace chex
