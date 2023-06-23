#include <sstream>
#include <string>
#include <vector>

#include "../board/board.hpp"

namespace chex {
using std::string, std::vector, std::stringstream;

vector<string> splitString(const std::string &str, char delimiter);
vector
string serializeBoardToJson(const Cell *board);

} // namespace chex
