#ifndef WEBUI_HPP
#define WEBUI_HPP

#include "../ui.hpp"
#include "../../lib/httplib.h"
#include <iostream>

#define HTTP_PORT 8080

using std::cout;

namespace chex {
  class WebUI : public BaseUI {
    public:
      void render() override;
  };
}

#endif
