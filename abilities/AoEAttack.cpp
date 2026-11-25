#include "AoEAttack.h"

#include <cstdlib>

AoEAttack::AoEAttack(int radius, int damage)
    : radius_(radius), damage_(damage) {}

bool AoEAttack::UseAbility(Robot& user, Map& map) {
  if (user.GetHealth() <= 0) return false;

  for (Robot* robot : map.GetRobots()) {
    if ((std::abs(user.GetPosX() - robot->GetPosX()) <= radius_) &&
        (std::abs(user.GetPosY() - robot->GetPosY()) <= radius_) &&
        (robot != &user)) {
      robot->TakeDamage(damage_);
    }
  }
  user.ConsumeEnergy(energy_cost_);

  return true;
}

void AoEAttack::UpgradeAbility() { radius_ += upgrade_area_; }