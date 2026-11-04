#include "Map.h"

#include <algorithm>
#include <random>

#include "Robot.h"
#include "RobotFactory.h"

Map::Map(int width, int height)
    : width_(std::clamp(width, kMinSize, kMaxSize)),
      height_(std::clamp(height, kMinSize, kMaxSize)) {
  InitMap();
}

Map::~Map() {
  for (Robot* robot : robots_) {
    delete robot;
  }
  for (RobotFactory* factory : factories_) {
    delete factory;
  }
}

int Map::GetWidth() const { return width_; }
int Map::GetHeight() const { return height_; }

bool Map::IsValidPosition(int x, int y) const {
  return x >= 0 && x < width_ && y >= 0 && y < height_;
}

Cell* Map::GetCell(int x, int y) {
  if (!IsValidPosition(x, y)) return nullptr;
  return &grid_[y][x];
}

const Cell* Map::GetCell(int x, int y) const {
  if (!IsValidPosition(x, y)) return nullptr;
  return &grid_[y][x];
}

bool Map::IsCellWalkable(int x, int y) const {
  if (!IsValidPosition(x, y)) return false;
  const Cell& cell = grid_[y][x];

  for (auto robot : robots_) {
    if (x == robot->GetPosX() && y == robot->GetPosY()) {
      return false;
    }
  }

  return cell.GetCellType() != CellType::kWall &&
         cell.GetCellType() != CellType::kFactory;
}

const std::vector<Robot*>& Map::GetRobots() const { return robots_; }

void Map::AddRobot(Robot* robot) { robots_.push_back(robot); }

void Map::DeleteRobot(Robot* robot) { std::erase(robots_, robot); }

const std::vector<RobotFactory*>& Map::GetFactories() const {
  return factories_;
}

void Map::AddFactory(RobotFactory* factory) { factories_.push_back(factory); }

void Map::DeleteFactory(RobotFactory* factory) {
  std::erase(factories_, factory);
}

void Map::InitMap() {
  constexpr int kWallSpawnThreshold = 85;
  constexpr int kAlternativeFreeThreshold = 65;

  constexpr int kSpawnZoneMaxSize = 2;
  constexpr int kFactoryZoneMin = 8;
  constexpr int kFactoryZoneMax = 10;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(1, 100);

  grid_.resize(height_);
  for (int y = 0; y < height_; ++y) {
    grid_[y].reserve(width_);
    for (int x = 0; x < width_; ++x) {
      bool is_spawn_zone = (x < kSpawnZoneMaxSize && y < kSpawnZoneMaxSize);
      bool is_factory_zone = (x >= kFactoryZoneMin && y >= kFactoryZoneMin &&
                              x < kFactoryZoneMax && y < kFactoryZoneMax);

      if (is_spawn_zone || is_factory_zone) {
        grid_[y].emplace_back(CellType::kFree, 1);
        continue;
      }

      int random_number = dist(gen);
      if (random_number > kWallSpawnThreshold) {
        grid_[y].emplace_back(CellType::kWall, 1);
      } else if (random_number > kAlternativeFreeThreshold) {
        grid_[y].emplace_back(CellType::kFree, 2);
      } else {
        grid_[y].emplace_back(CellType::kFree, 1);
      }
    }
  }
}

void Map::UpdateVisibility(int center_x, int center_y, int vision_radius) {
  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      grid_[y][x].SetVisible(false);
    }
  }

  for (int dy = -vision_radius; dy <= vision_radius; ++dy) {
    for (int dx = -vision_radius; dx <= vision_radius; ++dx) {
      int new_x = center_x + dx;
      int new_y = center_y + dy;
      if (IsValidPosition(new_x, new_y)) {
        grid_[new_y][new_x].SetVisible(true);
      }
    }
  }
}