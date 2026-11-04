#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "Map.h"
#include "Move.h"

class Robot;
class RobotFactory;

enum class GameState { kInProgress, kPlayerWon, kPlayerLost };

class Game {
 public:
  Game(int map_width, int map_height);

  bool AddPlayerRobot(int x, int y);
  bool AddEnemyRobot(int x, int y);
  bool AddFactory(int x, int y, int spawn_interval);

  bool PlayerMove(Direction direction);

  const Map& GetMap() const;
  const Robot* GetPlayer() const;
  const std::vector<Robot*>& GetEnemies() const;
  GameState GetState() const;
  int GetMoveCount() const;

 private:
  static constexpr int kEnergyRegenPerTurn = 5;
  void EndMove();
  void EnemyMove();
  void CleanupDeadRobots();
  void CheckGameState();
  Map map_;
  Robot* player_;
  GameState state_;
  int moves_count_;
};

#endif