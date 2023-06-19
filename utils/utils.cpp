#include "./utils.hpp"

namespace chex {

string serializeBoardToJson(const Cell* board) {
  std::stringstream ss;
  ss << "{";
  
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      const chex::Cell* cell = board + (i * BOARD_SIZE + j);
      
      ss << "\"" << i << "-" << j << "\": {";
      ss << "\"state\": \"" << (cell->state == chex::EMPTY ? "empty" : "filled") << "\"";
      
      if (cell->state == chex::FILLED && cell->piece != nullptr) {
        ss << ", \"piece\": {";
        ss << "\"type\": " << cell->piece->type << ",";
        ss << "\"color\": " << cell->piece->color << ",";
        ss << "\"position\": {\"x\": " << cell->piece->position.x << ", \"y\": " << cell->piece->position.y << "}";
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

vector<string> splitString(string str, const char delem) {
  vector<string> tokens;
  for (int i = 0; i < str.length(); i++) {
    string::size_type idx = str.find(delem);
    if (idx < 0) {
      tokens.push_back(str);
      return tokens;
    }
    tokens.push_back(str.substr(i, idx));
    i += idx;
  }
  return tokens;
}
} // namespace chex
