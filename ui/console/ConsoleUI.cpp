#include "./ConsoleUI.hpp"
#include <cstdlib>



namespace chex {

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void help() {
    printf("board    -- print the current board\n");
    printf("help     -- print this help message\n");
    printf("quit     -- quit the game\n");
    printf("move     -- make a move\n");
    printf("cls      -- clear the screen\n");
}

void welcome() {
  printf("\n\tWelcome to Chex::ConsoleUI! type `help` to see the list of commands\n");
}

void ConsoleUI::printBoard() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (game.chessBoard.board[i][j].state == CellState::FILLED) {
        const ChessPiece *piece = game.chessBoard.board[i][j].piece;
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

  void ConsoleUI::render(const int port) {
    (void)port;

    bool running = true;
    std::string command;

    welcome();

    while (running) {
      std::cout << "> ";
      std::getline(std::cin, command);

      if (command == "quit") {
        running = false;
      } else if (command == "help") {
        help();
      } else if (command == "board") {
        printBoard();
      } else if (command == "cls") {
        clearScreen();
      }
    }
}
  }
