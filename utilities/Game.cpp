#include "Game.h"

#include <algorithm>
#include <cmath>

#include "Cell.h"
#include "Move.h"
#include "Robot.h"
#include "RobotFactory.h"

Game::Game(int map_width, int map_height)
    : map_(map_width, map_height),
      player_(nullptr),
      state_(GameState::kInProgress),
      moves_count_(1) {}
bool Game::AddPlayerRobot(int x, int y) {
  if (!map_.IsCellWalkable(x, y)) return false;

  player_ = new Robot(100, 100, 15, 2, Team::kPlayer, x, y);
  map_.UpdateVisibility(x, y, player_->GetVisionRadius());
  map_.AddRobot(player_);

  return true;
}

bool Game::AddEnemyRobot(int x, int y) {
  if (!map_.IsCellWalkable(x, y)) return false;

  Robot* enemy = new Robot(100, 100, 15, 2, Team::kEnemy, x, y);
  map_.AddRobot(enemy);
  return true;
}

bool Game::AddFactory(int x, int y, int spawn_interval) {
  for (int dy = 0; dy < 2; ++dy) {
    for (int dx = 0; dx < 2; ++dx) {
      if (!map_.IsCellWalkable(x + dx, y + dy)) {
        return false;
      }
    }
  }

  for (int dy = 0; dy < 2; ++dy) {
    for (int dx = 0; dx < 2; ++dx) {
      Cell* cell = map_.GetCell(x + dx, y + dy);
      if (cell) {
        cell->SetCellType(CellType::kFactory);
      }
    }
  }
  RobotFactory* factory = new RobotFactory(x, y, spawn_interval);
  map_.AddFactory(factory);
  return true;
}

bool Game::PlayerMove(Direction direction) {
  if (state_ != GameState::kInProgress || !player_ || player_->GetHealth() <= 0)
    return false;

  bool made_any_move = false;

  while (player_->GetMovePoints() > 0) {
    bool step_success = Move::TryToMove(*player_, direction, map_);

    if (!step_success) break;

    made_any_move = true;
    map_.UpdateVisibility(player_->GetPosX(), player_->GetPosY(),
                          player_->GetVisionRadius());
  }

  if (made_any_move) {
    EndMove();
    return true;
  }

  CheckGameState();
  return false;
}

void Game::EndMove() {
  CleanupDeadRobots();
  CheckGameState();

  if (state_ != GameState::kInProgress) return;

  EnemyMove();

  for (auto factory : map_.GetFactories()) {
    factory->UpdateAndTrySpawn(*this);
  }

  CleanupDeadRobots();

  if (player_ && player_->GetHealth() > 0) {
    player_->RestoreEnergy(kEnergyRegenPerTurn);
    player_->ResetMovePoints();
  }

  for (auto& enemy : map_.GetRobots()) {
    if (enemy == player_) {
      continue;
    }
    enemy->RestoreEnergy(kEnergyRegenPerTurn);
    enemy->ResetMovePoints();
  }

  CheckGameState();
  ++moves_count_;
}

void Game::EnemyMove() {
  if (!player_) return;

  int player_x = player_->GetPosX();
  int player_y = player_->GetPosY();

  for (auto& enemy : map_.GetRobots()) {
    if (enemy == player_) {
      continue;
    }
    while (enemy->GetMovePoints() > 0) {
      int enemy_x = enemy->GetPosX();
      int enemy_y = enemy->GetPosY();

      Direction best_dir = Direction::kUp;

      if (std::abs(player_x - enemy_x) > std::abs(player_y - enemy_y)) {
        best_dir = (player_x > enemy_x) ? Direction::kRight : Direction::kLeft;
      } else {
        best_dir = (player_y > enemy_y) ? Direction::kDown : Direction::kUp;
      }

      bool moved = Move::TryToMove(*enemy, best_dir, map_);

      if (!moved) {
        enemy->UseMovePoints(enemy->GetMovePoints());
        break;
      }
    }
  }
}

void Game::CleanupDeadRobots() {
  for (auto robot : map_.GetRobots()) {
    if (robot->GetHealth() <= 0) {
      map_.DeleteRobot(robot);
    }
  }
}

void Game::CheckGameState() {
  if (!player_ || player_->GetHealth() <= 0 || player_->GetEnergy() < 6) {
    state_ = GameState::kPlayerLost;
  } else if (map_.GetRobots().size() == 1) {
    state_ = GameState::kPlayerWon;
  }
}

const Map& Game::GetMap() const { return map_; }
const Robot* Game::GetPlayer() const { return player_; }
GameState Game::GetState() const { return state_; }
int Game::GetMoveCount() const { return moves_count_; }