#include "./game.hpp"

namespace chex {
void Game::makeMove(ChessMove *move) { chessBoard.makeMove(move); }

MoveValidity Game::validateMove(ChessMove *move) const { return chessBoard.validateMove(move); }

void Game::undoMove() { chessBoard.undoMove(); }

Cell *Game::getBoard() { return &(chessBoard.board[0][0]); }

}; // namespace chex
