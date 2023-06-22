#ifndef WEBUI_HPP
#define WEBUI_HPP

#include "../ui.hpp"
#include <cassert>

#ifdef _WIN32
    #define CHEX_ON_WINDOWS
#else
    #define CHEX_ON_UNIX
    #include "../../lib/httplib.h"
#endif


#include <iostream>
#include <string>

using std::cout, std::string;

namespace chex {
  class WebUI : public BaseUI {
    public:
      void render(const int port = 8080) override;
  };
}

#endif
