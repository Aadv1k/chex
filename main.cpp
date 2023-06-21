#include "./ui/web/WebUI.hpp"
#include "./board/board.hpp"
#include <iostream>
#include <cstring>

using namespace std;
using namespace chex;

void graphic() {
  printf("           /$$                          \n");
  printf("          | $$                          \n");
  printf("  /$$$$$$$| $$$$$$$   /$$$$$$  /$$   /$$\n");
  printf(" /$$_____/| $$__  $$ /$$__  $$|  $$ /$$/\n");
  printf("| $$      | $$  \\ $$| $$$$$$$$ \\  $$$$/ \n");
  printf("| $$      | $$  | $$| $$_____/  >$$  $$ \n");
  printf("|  $$$$$$$| $$  | $$|  $$$$$$$ /$$/  $$\n");
  printf(" \\_______/|__/  |__/ \\_______/|__/  \\__/\n");
  printf("\n\tTHE HOMEGROWN CHESS ENGINE\n\n");
}

void usage(const char * target) {
  printf("Usage:\n");
  printf("\t%s web --port 8000\n", target);
  printf("Commands:\n");
  printf("\tweb         Start Chex on a local web server\n");
  printf("\thelp        Print this help message\n");
  printf("Options:\n");
  printf("\t--port, -p  Specify the port for the server (default: 8080)\n");
  exit(1);
}

int main(int argc, char** argv) {
  if (argc == 1) {
    graphic();
    usage(argv[0]);
  }

  bool web_mode = false; 
  int port = 8080;

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "web") == 0) {
      web_mode = true;
    } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) {
      if (!argv[i+1]) {
        fprintf(stderr, "[error] port was not provided to %s\n", argv[i]);
        usage(argv[0]);
      }
      i+=1;
      try {
        port = stoi(argv[i]);
      } catch (const std::invalid_argument&) {
        fprintf(stderr, "[error] port must be valid integer got %s\n", argv[i]);
        exit(1);
      }
    } else {
      usage(argv[0]);
    }
  }

  if (web_mode) {
    WebUI wui;
    wui.render(port);
  } else {
    fprintf(stderr, "[warn] no mode was specified!\n");
    exit(1);
  }
}


