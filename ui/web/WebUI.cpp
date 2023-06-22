#include "./WebUI.hpp"
#include "../../utils/utils.hpp"
#include "./index.h"

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

      ChessMove move = {.from = {.x = stoi(from[0]), .y = stoi(from[1])},
                        .to = {.x = stoi(to[0]), .y = stoi(to[1])}};

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

  cout << "server listening on "
       << "http://localhost:" << port << "\n";
  server.listen("0.0.0.0", port);
}

#else
void WebUI::http_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  (void)fn_data;

  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *)ev_data;
    if (mg_http_match_uri(hm, "/")) {
      mg_http_reply(c, 200, "Content-Type: text/html\r\n", INDEX_HTML, MG_ESC("status"), 1);
    } else if (mg_http_match_uri(hm, "/style.css")) {
      mg_http_reply(c, 200, "Content-Type: text/css\r\n", STYLE_CSS, MG_ESC("status"), 1);
    } else if (mg_http_match_uri(hm, "/script.js")) {
      mg_http_reply(c, 200, "Content-Type: text/javascript\r\n", SCRIPT_JS, MG_ESC("status"), 1);
    } else if (mg_http_match_uri(hm, "/board")) {
      mg_http_reply(c, 200, "Content-Type: application/json\r\n",
                    serializeBoardToJson(game.getBoard()).c_str(), MG_ESC("status"), 1);
    } else if (mg_http_match_uri(hm, "/move")) {

      string query = string(hm->query.ptr).substr(0, hm->query.len);

      vector<string> vec1 = splitString(query, '=');

      vector<string> split = splitString(vec1[1], '.');
      vector<string> from = splitString(split[0], '-');
      vector<string> to = splitString(split[1], '-');

      ChessMove move = {.from = {.x = stoi(from[0]), .y = stoi(from[1])},
                        .to = {.x = stoi(to[0]), .y = stoi(to[1])}};

      MoveValidity valid = game.validateMove(&move);

      if (valid != MoveValidity::LegalMove) {
        mg_http_reply(c, 200, "Content-Type: text/plain\r\n", "bad move", MG_ESC("status"), 1);
        return;
      }
      game.makeMove(&move);
      mg_http_reply(c, 200, "Content-Type: text/plain\r\n", "done", MG_ESC("status"), 1);
    } else {
      struct mg_http_serve_opts opts = {.root_dir = ".",
                                        .ssi_pattern = NULL,
                                        .extra_headers = NULL,
                                        .mime_types = NULL,
                                        .page404 = NULL,
                                        .fs = NULL};
      mg_http_serve_dir(c, hm, &opts);
    }
  }
}

void WebUI::render(const int port) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);

  std::string listen_addr = "http://localhost:" + std::to_string(port);
  std::cout << "Server listening on " << listen_addr << "\n";

  auto http_handler_wrapper = [](struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    static_cast<WebUI *>(fn_data)->http_handler(c, ev, ev_data, fn_data);
  };

  mg_http_listen(&mgr, listen_addr.c_str(), http_handler_wrapper, this);

  for (;;)
    mg_mgr_poll(&mgr, 1000);
}

#endif

} // namespace chex
