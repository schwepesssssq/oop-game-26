#include "Move.h"

#include <algorithm>

#include "Cell.h"
#include "Map.h"
#include "Robot.h"

bool Move::TryToMove(Robot& robot, Direction direction, Map& map) {
  constexpr int kMoveEnergyCost = 6;

  if (robot.GetEnergy() < kMoveEnergyCost) {
    return false;
  }

  int robot_x = robot.GetPosX();
  int robot_y = robot.GetPosY();

  switch (direction) {
    case Direction::kUp:
      --robot_y;
      break;
    case Direction::kDown:
      ++robot_y;
      break;
    case Direction::kRight:
      ++robot_x;
      break;
    case Direction::kLeft:
      --robot_x;
      break;
  }

  if (!map.IsValidPosition(robot_x, robot_y)) return false;

  Cell* next_cell = map.GetCell(robot_x, robot_y);

  if (next_cell->GetCellType() == CellType::kWall ||
      next_cell->GetCellType() == CellType::kFactory)
    return false;

  for (auto another_robot : map.GetRobots()) {
    if (&robot == another_robot) {
      continue;
    }

    if (robot_x == another_robot->GetPosX() &&
        robot_y == another_robot->GetPosY()) {
      if (robot.GetMovePoints() < 1) return false;

      robot.ConsumeEnergy(kMoveEnergyCost);
      robot.Interact(*another_robot);

      if (another_robot->GetHealth() <= 0) {
        map.DeleteRobot(another_robot);
        robot.SetPosition(robot_x, robot_y);
        return true;
      }

      return false;
    }
  }

  int cost = next_cell->GetMoveCost();
  if (robot.GetMovePoints() < cost) return false;

  robot.UseMovePoints(cost);
  robot.ConsumeEnergy(kMoveEnergyCost);
  robot.SetPosition(robot_x, robot_y);

  return true;
}