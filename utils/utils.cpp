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

    vector<string> splitString(const string& str, const char delim) {
        vector<string> tokens;
        string::size_type start = 0;
        string::size_type end = str.find(delim);

        while (end != string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + 1;
            end = str.find(delim, start);
        }

        tokens.push_back(str.substr(start));
        return tokens;
    }
} // namespace chex
