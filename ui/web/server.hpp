#ifndef UI_WEB_SERVER_HPP
#define UI_WEB_SERVER_HPP

#include "../../game/game.hpp"



namespace chex {
  class WebServer {
    init(int port = 8080);
  }

  private:
    Game game;
}

#endif
