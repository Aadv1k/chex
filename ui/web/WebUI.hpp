#ifndef WEBUI_HPP
#define WEBUI_HPP

#include "../ui.hpp"
#include "../../lib/httplib.h"

#ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
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
