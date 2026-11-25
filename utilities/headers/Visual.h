#ifndef VISUAL_H
#define VISUAL_H

#include "../../abilities/Ability.h"
class Game;

class Visual {
 public:
  Visual() = delete;
  static void Render(const Game& game);
};

#endif