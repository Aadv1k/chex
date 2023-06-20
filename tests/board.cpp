#include "../board/board.hpp"
#include "./test.hpp"

using namespace chex;

int main() {
  Board b;

  b.print();
  std::cout << "\n";

  ChessMove move1 = {.from = {4, 6}, .to = {4, 5}};
  b.makeMove(&move1);
  b.print();
  std::cout << "\n";

  ChessMove move2 = {.from = {4, 1}, .to = {4, 2}};
  b.makeMove(&move2);
  b.print();
  std::cout << "\n";

  ChessMove move3 = {.from = {4, 7}, .to = {4, 6}};
  b.makeMove(&move3);
  b.print();
  std::cout << "\n";

  b.undoMove();
  b.print();
  std::cout << "\n";

  std::cout << "ILLEGAL MOVE" << "\n";
  ChessMove move4 = {.from = {6, 1}, .to = {5, 2}};
  b.makeMove(&move4);
  b.print();
  std::cout << "\n";

  return 0;
}
