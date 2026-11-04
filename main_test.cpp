// g++ -std=c++20 -Ifuncs/headers funcs/*.cpp main_test.cpp -o run_tests

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#include "Cell.h"
#include "Game.h"
#include "Map.h"
#include "Move.h"
#include "Robot.h"
#include "RobotFactory.h"

#define TEST_CASE(name) void name()
#define REQUIRE(condition)                                                  \
  if (!(condition)) {                                                       \
    std::cerr << "FAIL: " << #condition << " at line " << __LINE__ << "\n"; \
    std::exit(1);                                                           \
  } else {                                                                  \
    std::cout << "PASS: " << #condition << "\n";                            \
  }

TEST_CASE(TestClassRobot) {
  std::cout << "\nTesting Class: Robot\n";

  Robot player(100, 100, 20, 2, Team::kAlly, 0, 0);
  Robot enemy(30, 50, 10, 1, Team::kEnemy, 1, 0);

  player.TakeDamage(40);
  REQUIRE(player.GetCurrentHealth() == 60);

  player.Heal(100);
  REQUIRE(player.GetCurrentHealth() == 100);

  REQUIRE(player.IsEnemy(enemy) == true);

  bool action_result = player.Interact(enemy);
  REQUIRE(action_result == true);
  REQUIRE(enemy.GetCurrentHealth() == 10);

  player.AddExperience(15);
  REQUIRE(player.GetRank() == 2);
  REQUIRE(player.GetMaxHealth() == 110);
}

TEST_CASE(TestClassCell) {
  std::cout << "\nTesting Class: Cell\n";

  Cell cell(CellType::kFree, 1);

  REQUIRE(cell.IsVisible() == false);

  cell.SetVisible(true);
  REQUIRE(cell.IsVisible() == true);

  cell.SetVisible(false);
  REQUIRE(cell.IsVisible() == false);

  cell.SetDiscovered(true);
  REQUIRE(cell.IsDiscovered() == true);
}

TEST_CASE(TestClassMap) {
  std::cout << "\nTesting Class: Map\n";

  Map map(10, 10);

  REQUIRE(map.IsValidPosition(0, 0) == true);
  REQUIRE(map.IsValidPosition(9, 9) == true);
  REQUIRE(map.IsValidPosition(-1, 5) == false);
  REQUIRE(map.IsValidPosition(10, 10) == false);

  Cell* cell_near = map.GetCell(5, 5);
  Cell* cell_far = map.GetCell(0, 0);

  REQUIRE(cell_near->IsVisible() == false);

  map.UpdateVisibility(5, 5, 2);

  REQUIRE(cell_near->IsVisible() == true);
  REQUIRE(cell_far->IsVisible() == false);

  Robot* test_robot = new Robot(100, 100, 10, 1, Team::kAlly, 3, 3);
  map.AddRobot(test_robot);
  REQUIRE(map.IsCellWalkable(3, 3) == false);
}

TEST_CASE(TestClassRobotFactory) {
  std::cout << "\nTesting Class: RobotFactory\n";

  Game game(15, 15);
  RobotFactory factory(8, 8, 2);

  REQUIRE((game.GetMap().GetRobots().size()) == 0);

  factory.UpdateAndTrySpawn(game);
  REQUIRE((game.GetMap().GetRobots().size()) == 0);

  factory.UpdateAndTrySpawn(game);
  REQUIRE((game.GetMap().GetRobots().size()) == 1);
}

TEST_CASE(TestClassMove) {
  std::cout << "\nTesting Class: Move\n";

  Map map(10, 10);
  Robot* robot = new Robot(100, 100, 10, 2, Team::kAlly, 0, 0);
  map.AddRobot(robot);

  Cell* target_cell = map.GetCell(1, 0);
  target_cell->SetCellType(CellType::kFree);
  target_cell->SetMoveCost(1);

  robot->ResetMovePoints();

  bool move_success = Move::TryToMove(*robot, Direction::kRight, map);

  REQUIRE(move_success == true);
  REQUIRE(robot->GetPosX() == 1);
  REQUIRE(robot->GetPosY() == 0);
  REQUIRE(map.IsCellWalkable(1, 0) == false);
}

TEST_CASE(TestClassGame) {
  std::cout << "\nTesting Class: Game\n";

  Game game(10, 10);

  REQUIRE(game.GetState() == GameState::kInProgress);

  game.AddPlayerRobot(0, 0);
  game.AddEnemyRobot(1, 0);

  REQUIRE(game.GetPlayer() != nullptr);
  REQUIRE((game.GetMap().GetRobots().size() - 1) == 1);

  game.PlayerMove(Direction::kRight);
  game.PlayerMove(Direction::kRight);
  game.PlayerMove(Direction::kRight);
  game.PlayerMove(Direction::kRight);
  game.PlayerMove(Direction::kRight);
  game.PlayerMove(Direction::kRight);
  game.PlayerMove(Direction::kRight);

  if (game.GetMap().GetRobots().size() == 1) {
    REQUIRE(game.GetState() == GameState::kPlayerWon);
  }
}

int main() {
  std::cout << "RUNNING ALL CLASSES UNIT TESTS\n";

  TestClassRobot();
  TestClassCell();
  TestClassMap();
  TestClassRobotFactory();
  TestClassMove();
  TestClassGame();

  std::cout << "\nALL UNIT TESTS PASSED SUCCESSFULLY!\n";
  return 0;
}
