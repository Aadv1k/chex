#ifndef WEBUI_HPP
#define WEBUI_HPP

#include "../ui.hpp"
#include <cassert>

#ifdef _WIN32
    #define CHEX_ON_WINDOWS
    #include "../../lib/mongoose.hpp"
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
#ifdef _WIN32
    private:
      void http_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
#endif

};
}

#endif
