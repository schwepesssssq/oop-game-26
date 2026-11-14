#include "Robot.h"

#include <algorithm>

Robot::Robot(int max_health, int max_energy, int attack, int speed, Team team,
             int x, int y)
    : max_health_(std::max(1, max_health)),
      health_(max_health_),
      max_energy_(std::max(1, max_energy)),
      energy_(max_energy_),
      attack_(std::max(1, attack)),
      speed_(std::max(1, speed)),
      team_(team),
      current_experience_(0),
      experience_to_rank_up_(10),
      rank_(1),
      position_x_(x),
      position_y_(y),
      move_points_(speed),
      vision_radius_(5) {}

Robot::Robot() : Robot(100, 100, 1, 1, Team::kEnemy, 0, 0) {}

int Robot::GetHealth() const { return health_; }
int Robot::GetMaxHealth() const { return max_health_; }
int Robot::GetEnergy() const { return energy_; }
int Robot::GetMaxEnergy() const { return max_energy_; }
int Robot::GetAttack() const { return attack_; }
int Robot::GetCurrentExperience() const { return current_experience_; }
int Robot::GetExperienceToRankUp() const { return experience_to_rank_up_; }
int Robot::GetRank() const { return rank_; }
int Robot::GetSpeed() const { return speed_; }
Team Robot::GetTeam() const { return team_; }
int Robot::GetPosX() const { return position_x_; }
int Robot::GetPosY() const { return position_y_; }
int Robot::GetVisionRadius() const { return vision_radius_; }

void Robot::SetPosition(int x, int y) {
  position_x_ = x;
  position_y_ = y;
}

void Robot::SetVisionRadius(int radius) {
  vision_radius_ = std::max(1, radius);
}

bool Robot::Heal(int health_points) {
  if (health_points <= 0) return false;
  health_ = std::min(health_ + health_points, max_health_);
  return true;
}

bool Robot::TakeDamage(int damage_points) {
  if (damage_points <= 0) return false;
  health_ = std::max(health_ - damage_points, 0);
  return true;
}

bool Robot::RestoreEnergy(int energy_points) {
  if (energy_points <= 0) return false;
  energy_ = std::min(energy_ + energy_points, max_energy_);
  return true;
}

bool Robot::ConsumeEnergy(int energy_points) {
  if (energy_points <= 0) return false;
  energy_ = std::max(energy_ - energy_points, 0);
  return true;
}

bool Robot::AddExperience(int experience_points) {
  if (experience_points <= 0) return false;
  current_experience_ += experience_points;
  CheckRankUp();
  return true;
}
bool Robot::IsEnemyWith(const Robot& other) const {
  if (team_ != other.GetTeam()) {
    return true;
  }
  return false;
}

bool Robot::Interact(Robot& target) {
  if (this == &target) return false;

  if (IsEnemyWith(target)) {
    target.TakeDamage(attack_);

    if (target.GetHealth() <= 0) {
      AddExperience(5);
      energy_ = max_energy_;
    }
  } else {
    target.Heal(attack_);
  }
  return true;
}

void Robot::CheckRankUp() {
  while (current_experience_ >= experience_to_rank_up_) {
    ++rank_;

    max_health_ += 10;
    health_ = max_health_;
    max_energy_ += 10;
    energy_ = max_energy_;
    attack_ += 1;

    experience_to_rank_up_ += 10;
  }
}

int Robot::GetMovePoints() const { return move_points_; }

void Robot::ResetMovePoints() { move_points_ = speed_; }

bool Robot::UseMovePoints(int points) {
  if (points <= 0 || move_points_ < points) return false;
  move_points_ -= points;
  return true;
}
