#ifndef STANDARD_NOTATION_PARSER_HPP
#define STANDARD_NOTATION_PARSER_HPP

#include "./NotationParser.hpp";
#include "../../utils/utils.h";

namespace chex {
class StandardNotationParser : NotationParser {
public:
  ChessMove *parse(const string notation) override;
}
#endif
