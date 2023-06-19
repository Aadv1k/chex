#include "./WebUI.hpp"

namespace chex {
  void WebUI::render() {
    httplib::Server server;

    server.Get("/", [](const httplib::Request &, httplib::Response &res) {
      res.set_content("Hello World!", "text/plain");
    });

    cout << "server listening on " << "http://localhost:" << HTTP_PORT << "\n";
    server.listen("0.0.0.0", HTTP_PORT);
  }
}
