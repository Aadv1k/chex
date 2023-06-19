#ifndef WEBUI_HPP
#define WEBUI_HPP

#include "../ui.hpp"
#include "../../lib/httplib.h"

#include <iostream>
#include <string>

#define HTTP_PORT 8000

using std::cout, std::string;

namespace chex {
  class WebUI : public BaseUI {
    public:
      void render() override;
  };
}

#endif
