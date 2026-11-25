#include "RangeAttack.h"

#include <cstdlib>
#include <iostream>

RangeAttack::RangeAttack(int range, int damage)
    : range_(range), damage_(damage) {}

bool RangeAttack::UseAbility(Robot& user, Map& map) {
  if (user.GetHealth() <= 0) return false;

  std::cout << "Введите координату x цели: " << std::endl;
  int x;
  std::cin >> x;

  std::cout << "Введите координату y цели: " << std::endl;
  int y;
  std::cin >> y;

  if ((x >= 0 && x <= map.GetWidth()) && (y >= 0 && y <= map.GetHeight())) {
    for (Robot* robot : map.GetRobots()) {
      if ((robot->GetPosX() == x) && (robot->GetPosY() == y) &&
          (robot != &user)) {
        if ((std::abs(user.GetPosX() - x) <= range_) &&
            (std::abs(user.GetPosY() - y) <= range_)) {
          robot->TakeDamage(damage_);
          user.ConsumeEnergy(energy_cost_);
          return true;
        }
      }
    }
  }

  return false;
}

void RangeAttack::UpgradeAbility() { damage_ += damage_increase_bonus_; }