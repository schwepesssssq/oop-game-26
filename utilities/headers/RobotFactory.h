#ifndef ROBOTFACTORY_H
#define ROBOTFACTORY_H

class Game; 

class RobotFactory {
 public:
  RobotFactory(int x, int y, int spawn_interval);

  bool UpdateAndTrySpawn(Game& game);

  int GetPositionX() const;
  int GetPositionY() const;
  int GetMoveCount() const;

 private:
  const int top_left_x_; 
  const int top_left_y_;
  int spawn_interval_;   
  int move_count_;
};

#endif