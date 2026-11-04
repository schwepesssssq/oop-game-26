#ifndef CONTROLLER_H
#define CONTROLLER_H

class Game;

class Controller {
 public:
  explicit Controller(Game& game);
  void Run();

 private:
  bool ProcessInput();

  Game& game_;
};

#endif
