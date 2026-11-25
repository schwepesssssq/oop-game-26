#include "Healing.h"

Healing::Healing(int healing_points) : healing_(healing_points) {}

bool Healing::UseAbility(Robot& user, Map& map) {
  if (user.GetHealth() <= 0) return false;

  user.Heal(healing_);
  user.ConsumeEnergy(energy_cost_);
  return true;
}

void Healing::UpgradeAbility() { healing_ += healing_increase_bonus_; }