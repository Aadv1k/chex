#ifndef CONSOLEUI_HPP
#define CONSOLEUI_HPP

#include "../ui.hpp"
#include "../../utils/utils.hpp"
#include <cassert>

#include <iostream>
#include <string>

using std::cout, std::string;

namespace chex {
  class ConsoleUI : public BaseUI {
    public:
      void render(const int port = 0) override;
    private:
      void printBoard();
    };
}

#endif
