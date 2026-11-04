#include "headers/Robot.h"

#include <algorithm>

Robot::Robot(int max_health, int attack_damage, int max_energy, int speed,
             Team team, int x, int y)
    : max_health_(std::max(1, max_health)),
      current_health_(max_health_),
      max_energy_(std::max(1, max_energy)),
      current_energy_(max_energy_),
      attack_damage_(std::max(1, attack_damage)),
      speed_(std::max(1, speed)),
      team_(team),
      current_experience_(0),
      experience_left_to_next_level_(10),
      rank_(1),
      pos_x_(x),
      pos_y_(y),
      move_points_(speed),
      vision_radius_(5) {}

Robot::Robot() : Robot(100, 100, 1, 1, Team::kEnemy, 0, 0) {}

int Robot::GetCurrentHealth() const { return current_health_; }
int Robot::GetMaxHealth() const { return max_health_; }
int Robot::GetAttackDamage() const { return attack_damage_; }
int Robot::GetCurrentEnergy() const { return current_energy_; }
int Robot::GetMaxEnergy() const { return max_energy_; }
int Robot::GetCurrentExperience() const { return current_experience_; }
int Robot::GetExperienceLeftToNextLevel() const {
  return experience_left_to_next_level_;
}
Team Robot::GetTeam() const { return team_; }
int Robot::GetRank() const { return rank_; }
int Robot::GetPosX() const { return pos_x_; }
int Robot::GetPosY() const { return pos_x_; }
int Robot::GetSpeed() const { return speed_; }
int Robot::GetVisionRadius() const { return vision_radius_; }

void Robot::SetPos(int x, int y) {
  pos_x_ = x;
  pos_y_ = y;
}

void Robot::SetVisionRadius(int radius) {
  vision_radius_ = std::max(1, radius);
}

bool Robot::Heal(int health_points) {
  if (health_points <= 0) return false;
  current_health_ = std::min(current_health_ + health_points, max_health_);
  return true;
}

bool Robot::TakeDamage(int damage_points) {
  if (damage_points <= 0) return false;
  current_health_ = std::max(current_health_ - damage_points, 0);
  return true;
}

bool Robot::RestoreEnergy(int energy_points) {
  if (energy_points <= 0) return false;
  current_energy_ = std::min(current_energy_ + energy_points, max_energy_);
  return true;
}

bool Robot::ConsumeEnergy(int energy_points) {
  if (energy_points <= 0) return false;
  current_energy_ = std::max(current_energy_ - energy_points, 0);
  return true;
}

bool Robot::AddExperience(int experience_points) {
  if (experience_points <= 0) return false;
  current_experience_ += experience_points;
  CheckRank();
  return true;
}

bool Robot::IsEnemy(const Robot& other) const {
  if (team_ != other.GetTeam()) {
    return true;
  }
  return false;
}

bool Robot::Interact(Robot& target) {
  if (this == &target) return false;

  if (IsEnemy(target)) {
    target.TakeDamage(attack_damage_);

    if (target.GetCurrentHealth() <= 0) {
      AddExperience(5);
      current_energy_ = max_energy_;
    }
  } else {
    target.Heal(attack_damage_);
  }
  return true;
}

void Robot::CheckRank() {
  while (current_experience_ >= experience_left_to_next_level_) {
    ++rank_;

    max_health_ += 10;
    max_energy_ += 10;
    attack_damage_ += 1;

    experience_left_to_next_level_ += 10;
  }
}

int Robot::GetMovePoints() const { return move_points_; }

void Robot::ResetMovePoints() { move_points_ = speed_; }

bool Robot::UseMovePoints(int points) {
  if (points <= 0 || move_points_ < points) return false;
  move_points_ -= points;
  return true;
}