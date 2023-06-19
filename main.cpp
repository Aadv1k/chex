#include "./game/game.hpp"
#include <iostream>


using namespace chex;
using namespace std;

int main() {
    Game g;

    Cell* boardPtr = g.getBoard();
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        Cell* currentCell = boardPtr + (i * BOARD_SIZE + j);
        cout << currentCell->piece->type << "\n";
      }
    }
}
