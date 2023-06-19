#ifndef UI_H
#define UI_H

#include "../game/game.hpp"

namespace chex {
class BaseUI {
public:
  Game game;
  virtual void render() = 0;
};

} // namespace chex

#endif
