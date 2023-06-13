#include "./utils.hpp"

namespace chex {
  using std::string, std::vector;

  vector<string> splitString(string str, const char delem) {
    vector<string> tokens;
    for (int i = 0; i < str.length(); i++) {
      string::size_type idx = str.find(delem);
      if (idx < 0) {
        tokens.push_back(str);
        return tokens;
      }
      tokens.push_back(str.substr(i, idx));
      i+=idx;
    }
    return tokens;
  }} 
