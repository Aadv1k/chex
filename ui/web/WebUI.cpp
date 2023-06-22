#include "./WebUI.hpp"
#include "./index.h" 
#include "../../utils/utils.hpp"


namespace chex {

#ifdef CHEX_ON_UNIX

  void WebUI::render(const int port) {
    httplib::Server server;

    server.Get("/", [](const httplib::Request &, httplib::Response &res) {
      res.set_content(INDEX_HTML, "text/html");
    });

    server.Get("/style.css", [this](const httplib::Request &, httplib::Response &res) {
      res.set_content(STYLE_CSS, "text/css");
    });

    server.Get("/script.js", [this](const httplib::Request &, httplib::Response &res) {
      res.set_content(SCRIPT_JS, "text/javascript");
    });


    server.Get("/board", [this](const httplib::Request &, httplib::Response &res) {
      res.set_content(serializeBoardToJson(game.getBoard()), "application/json");
    });

    server.Get("/undo", [this](const httplib::Request &, httplib::Response &res) {
      game.undoMove();
      res.status = 200;
      res.set_content("done", "text/plain");
    });

    server.Get("/move", [this](const httplib::Request &req, httplib::Response &res) {
      if (req.has_param("m")) {
        string val = req.get_param_value("m");
        res.status = 200;

        vector<string> split = splitString(val, '.');
        vector<string> from = splitString(split[0], '-');
        vector<string> to = splitString(split[1], '-');

        ChessMove move = {
          .from = {
            .x = stoi(from[0]),
            .y = stoi(from[1])
          },
          .to = {
            .x = stoi(to[0]),
            .y = stoi(to[1])
          }
        };

        MoveValidity valid = game.validateMove(&move);
        if (valid != MoveValidity::LegalMove) {
          res.set_content("bad move", "text/plain");
          return;
        }
        game.makeMove(&move);
        res.set_content("done", "text/plain");
      } else {
        res.status = 400;
        res.set_content("bad input", "text/plain");
      }
    });

    cout << "server listening on " << "http://localhost:" << port << "\n";
    server.listen("0.0.0.0", port);
  }

#else

  void WebUI::render(const int port) {
    assert(0 && "for windows not implemented");
  }

#endif
 
}
