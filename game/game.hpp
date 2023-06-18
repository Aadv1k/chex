#ifndef GAME_HPP
#define GAME_HPP

#include "../engine/board/board.hpp";
#include <cassert>


namespace chex {
  enum GameState {
    WhiteCheck,
    WhiteMate,
    BlackCheck,
    BlackMate
  }

  class Game {
    public: 
      MoveValidity makeMove(ChessMove * move);
      void undoMove();  
      std::array<std::array<Cell>> get2dBoard();
      GameState getGameState();
      stack<ChessPiece *> getCaptured();

    private:
      Board chessBoard;
  }
}
#endif
