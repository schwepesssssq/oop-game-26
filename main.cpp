#include "Controller.h"
#include "Game.h"

int main() {
  Game game(20, 20);

  game.AddPlayerRobot(0, 0);
  game.AddEnemyRobot(5, 5);
  game.AddEnemyRobot(8, 2);
  game.AddEnemyRobot(3, 7);
  game.AddFactory(8, 8, 10);

  Controller controller(game);
  controller.Run();

  return 0;
}
