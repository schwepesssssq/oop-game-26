#ifndef VISUAL_H
#define VISUAL_H

class Game;

class Visual {
 public:
  Visual() = delete;
  static void Render(const Game& game);
};

#endif