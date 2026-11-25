#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Cell.h"
#include "Robot.h"

class RobotFactory;

class Map {
 public:
  static constexpr int kMinSize = 5;
  static constexpr int kMaxSize = 50;

  Map(int width, int height);
  ~Map();

  int GetWidth() const;
  int GetHeight() const;

  bool IsValidPosition(int x, int y) const;

  Cell* GetCell(int x, int y);
  const Cell* GetCell(int x, int y) const;
  bool IsCellWalkable(int x, int y) const;

  const std::vector<Robot*>& GetRobots() const;
  void AddRobot(Robot* robot);
  void DeleteRobot(Robot* robot);

  const std::vector<RobotFactory*>& GetFactories() const;
  void AddFactory(RobotFactory* factory);
  void DeleteFactory(RobotFactory* factory);

  void UpdateVisibility(int center_x, int center_y, int vision_radius);

 private:
  void InitMap();

  int width_;
  int height_;
  std::vector<std::vector<Cell>> grid_;
  std::vector<Robot*> robots_;
  std::vector<RobotFactory*> factories_;
};

#endif