#include "./test.hpp"
#include "../engine/board/board.hpp"

using namespace chex;

int main () {
  Board b;
  b.print();
  ChessMove move1 = {
    .from = {1, 6},
    .to = {1, 5}
  };
  b.makeMove(&move1);
  b.print();
  std::cout << "\n";
  ChessMove move2 = {
    .from = {1, 1},
    .to = {1, 2}
  };
  b.makeMove(&move2);
  b.print();
  std::cout << "\n";
  ChessMove move3 = {
    .from = {1, 7},
    .to = {2, 5}
  };
  b.makeMove(&move3);
  b.print();
  std::cout << "\n";
  ChessMove move4 = {
    .from = {2, 0},
    .to = {0, 2}
  };
  b.makeMove(&move4);
  b.print();
  return 0;
}
