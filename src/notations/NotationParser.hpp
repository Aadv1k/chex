#ifndef NOTATION_PARSER_HPP
#define NOTATION_PARSER_HPP

#include "../board/board.hpp"  

#include <vector>
#include <string>

using std::vector, std::string;

namespace chex {
  class NotationParser {
    public:
     virtual ChessMove* parse(const string notation) = 0;
     virtual ~NotationParser() {};
  }
}

#endif
