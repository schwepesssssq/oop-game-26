#ifndef ROBOT_H
#define ROBOT_H

enum class Team {
  kAlly,
  kEnemy,
};

class Robot {
 public:
  Robot(int max_health, int attack_damage, int max_energy, int speed, Team team,
        int x, int y);
  Robot();

  int GetCurrentHealth() const;
  int GetMaxHealth() const;
  int GetAttackDamage() const;
  int GetCurrentEnergy() const;
  int GetMaxEnergy() const;
  int GetCurrentExperience() const;
  int GetExperienceLeftToNextLevel() const;
  int GetRank() const;
  Team GetTeam() const;
  int GetPosX() const;
  int GetPosY() const;
  int GetSpeed() const;
  int GetVisionRadius() const;

  void SetPos(int x, int y);
  void SetVisionRadius(int radius);
  bool TakeDamage(int damage_points);
  bool Heal(int health_points);
  bool RestoreEnergy(int energy_points);
  bool ConsumeEnergy(int energy_points);
  bool AddExperience(int experience_points);
  bool IsEnemy(const Robot& other) const;

  bool Interact(Robot& target);

  int GetMovePoints() const;
  void ResetMovePoints();
  bool UseMovePoints(int amount);

 private:
  void CheckRank();
  int current_health_;
  int max_health_;
  int attack_damage_;
  int current_energy_;
  int max_energy_;
  int current_experience_;
  int experience_left_to_next_level_;
  int speed_;
  int rank_;
  int vision_radius_;
  int move_points_;
  int pos_x_;
  int pos_y_;
  Team team_;
};

#endif
