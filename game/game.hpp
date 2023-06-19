#ifndef GAME_HPP
#define GAME_HPP

#include "../board/board.hpp"
#include <cassert>
#include <array>
#include <stack>

using std::array, std::stack;

namespace chex {
  enum GameState {
    WhiteCheck,
    WhiteMate,
    BlackCheck,
    BlackMate
  };

  class Game {
    public: 
      MoveValidity validateMove(ChessMove * move);
      void makeMove(ChessMove * move);
      void undoMove();  
      Cell* getBoard();

    private:
      Board chessBoard;
  };
}
#endif
