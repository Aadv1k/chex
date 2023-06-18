#include "./game.hpp";

namespace chex {
  MoveValidity Game::makeMove(ChessMove * move) {
    return chessBoard.makeMove(move);
  }

  void Game::undoMove() {
    chessBoard.undoMove(move);
  }

  std::array<std::array<Cell>> get2dBoard() {
    return chessBoard.board;
  }

  Game::getGameState() {
    assert(0 && "getGameState not implemented");
  }

  stack<ChessPiece *> Game::getCaptured() {
    return chessBoard.capturedStack; 
  }
}
