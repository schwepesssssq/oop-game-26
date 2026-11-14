#ifndef ROBOT_H
#define ROBOT_H

enum class Team {
  kPlayer,
  kEnemy,
};

class Robot {
 public:
  Robot(int max_health, int max_energy, int attack, int speed, Team team, int x,
        int y);
  Robot();

  int GetHealth() const;
  int GetMaxHealth() const;
  int GetEnergy() const;
  int GetMaxEnergy() const;
  int GetAttack() const;
  int GetCurrentExperience() const;
  int GetExperienceToRankUp() const;
  int GetRank() const;
  int GetSpeed() const;
  Team GetTeam() const;
  int GetPosX() const;
  int GetPosY() const;
  int GetVisionRadius() const;

  bool TakeDamage(int damage_points);
  bool Heal(int health_points);
  bool RestoreEnergy(int energy_points);
  bool ConsumeEnergy(int energy_points);
  bool AddExperience(int experience_points);
  void SetPosition(int x, int y);
  void SetVisionRadius(int radius);

  bool IsEnemyWith(const Robot& other) const;

  bool Interact(Robot& target);

  int GetMovePoints() const;
  void ResetMovePoints();
  bool UseMovePoints(int amount);

 private:
  void CheckRankUp();

  int max_health_;
  int health_;
  int max_energy_;
  int energy_;
  int attack_;
  int speed_;
  Team team_;
  int current_experience_;
  int experience_to_rank_up_;
  int rank_;
  int position_x_;
  int position_y_;
  int move_points_;
  int vision_radius_;
};

#endif