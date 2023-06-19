#include <string>
#include <sstream>
#include <vector>

#include "../board/board.hpp"

namespace chex {
using std::string, std::vector, std::stringstream;

vector<string> splitString(string str, const char delem);
string serializeBoardToJson(const Cell* board);

} // namespace chex
