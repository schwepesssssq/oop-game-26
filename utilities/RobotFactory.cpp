#include "RobotFactory.h"

#include <vector>

#include "Game.h"

RobotFactory::RobotFactory(int x, int y, int spawn_interval)
    : top_left_x_(x),
      top_left_y_(y),
      spawn_interval_((spawn_interval > 0) ? spawn_interval : 3),
      move_count_(0) {}

bool RobotFactory::UpdateAndTrySpawn(Game& game) {
  ++move_count_;

  if (move_count_ < spawn_interval_) {
    return false;
  }

  move_count_ = 0;

  const Map& map = game.GetMap();
  std::vector<std::pair<int, int>> free_cells;

  for (int x = top_left_x_ - 1; x <= top_left_x_ + 2; ++x) {
    for (int y = top_left_y_ - 1; y <= top_left_y_ + 2; ++y) {
      if (x >= top_left_x_ && x <= top_left_x_ + 1 &&
          y >= top_left_y_ && y <= top_left_y_ + 1) {
        continue;
      }

      if (map.IsCellWalkable(x, y)) {
        free_cells.emplace_back(x, y);
      }
    }
  }

  if (free_cells.empty()) {
    return false;
  }

  auto [spawn_x, spawn_y] = free_cells.front();
  return game.AddEnemyRobot(spawn_x, spawn_y);
}

int RobotFactory::GetPositionX() const { return top_left_x_; }
int RobotFactory::GetPositionY() const { return top_left_y_; }
int RobotFactory::GetMoveCount() const { return move_count_; }