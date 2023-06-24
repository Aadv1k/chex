#include "./utils.hpp"

namespace chex {

string serializeBoardToJson(const Cell *board) {
  std::stringstream ss;
  ss << "{";

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      const chex::Cell *cell = board + (i * BOARD_SIZE + j);

      ss << "\"" << i << "-" << j << "\": {";
      ss << "\"state\": \"" << (cell->state == chex::EMPTY ? "empty" : "filled") << "\"";

      if (cell->state == chex::FILLED && cell->piece != nullptr) {
        ss << ", \"piece\": {";
        ss << "\"type\": " << cell->piece->type << ",";
        ss << "\"color\": " << cell->piece->color << ",";
        ss << "\"position\": {\"x\": " << cell->piece->position.x
           << ", \"y\": " << cell->piece->position.y << "}";
        ss << "}";
      }

      ss << "}, ";
    }
  }

  string serializedJson = ss.str();

  // Remove the trailing comma and space
  serializedJson = serializedJson.substr(0, serializedJson.length() - 2);

  serializedJson += "}";
  return serializedJson;
}

std::vector<std::string> splitString(const std::string &str, char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;
  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

/* simple but workrs for our case */
string trim(const string str) {
  string ret = str;
  return ret.substr(ret.find_first_not_of(' '), ret.find_last_not_of(' ') + 1);
}

} // namespace chex
