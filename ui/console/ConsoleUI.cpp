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
  printf("\n-----------------------------------------------------\n");
  printf("                  Available commands\n");
  printf("-----------------------------------------------------\n\n");
  printf("   - board: Print the current state of the chessboard.\n");
  printf("   - move <pos> <pos>: Make a move by specifying the starting and ending positions.\n");
  printf("   - cls: Clear the screen.\n");
  printf("   - quit: Quit the game.\n");
  printf("   - help: Display this help message.\n");
}

void welcome() {
  printf("\n-----------------------------------------------------\n");
  printf("           Welcome to Chex::ConsoleUI!\n");
  printf("-----------------------------------------------------\n");
  printf("Type 'help' to see the list of available commands.\n\n");
}

void ConsoleUI::printBoard() {
  std::cout << "\n";

  for (int i = 0; i < BOARD_SIZE; i++) {
    std::cout << "  ";
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (j == 0) {
        std::cout << i + 1 << " ";
      }

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
    if (i == BOARD_SIZE - 1) {
      std::cout << "    a b c d e f g h\n\n";
    }
  }
}

void ConsoleUI::render(const int port) {
  (void)port;

  bool running = true;
  std::string command;

  clearScreen();
  welcome();

  while (running) {
    PieceColor currentPlayer = PieceColor::WHITE;
    printf("%s turn> ", currentPlayer == PieceColor::WHITE ? "white's" : "black's");
    std::getline(std::cin, command);

    if (command.length() == 0) {
      continue;
    }

    command = trim(command);

    if (command == "quit") {
      running = false;
    } else if (command == "help") {
      clearScreen();
      help();
    } else if (command == "board") {
      clearScreen();
      printBoard();
    } else if (command == "cls") {
      clearScreen();
    } else if (command.substr(0, 4) == "move") {
      std::vector<std::string> split = splitString(command, ' ');
      if (split.size() != 3) {
        printf("Error: Invalid command. Please specify both the starting and ending positions.\n");
        continue;
      }

      std::string from = split[1];
      std::string to = split[2];

      try {
        int toY = std::stoi(to.substr(1));
        int toX = static_cast<int>(to[0]) - 'a' + 1;

        int fromY = std::stoi(from.substr(1));
        int fromX = static_cast<int>(from[0]) - 'a' + 1;

        if ((toX > BOARD_SIZE || toY > BOARD_SIZE) || (fromX > BOARD_SIZE || fromY > BOARD_SIZE)) {
          printf("Error: Invalid notation. Positions are out of range.\n");
          continue;
        }

        ChessMove move = {.from = {.x = fromX - 1, .y = fromY - 1},
                          .to = {.x = toX - 1, .y = toY - 1}};

        if (game.validateMove(&move) != MoveValidity::LegalMove) {
          printf("Illegal move!\n");
          continue;
        }

        game.makeMove(&move);
        clearScreen();
        printBoard();
        currentPlayer = currentPlayer == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE;

      } catch (const std::exception &e) {
        printf("Error: Invalid command. Please use the standard chess notation.\nExample: move e3 "
               "e4\n");
        continue;
      }
    } else {
      printf("Error: Invalid command. Type 'help' to see the list of available commands.\n");
    }
  }
}

} // namespace chex
