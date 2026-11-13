#ifndef MOVE_H
#define MOVE_H


class Robot;
class Map;

enum class Direction {
  kUp,
  kDown,
  kLeft,
  kRight,
};

class Move {
 public:
  static bool TryToMove(Robot& robot, Direction direction, Map& map);
};

#endif