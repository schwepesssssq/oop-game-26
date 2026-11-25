#include "Teleportation.h"

#include <cstdlib>
#include <iostream>

Teleportation::Teleportation(int radius) : radius_(radius) {};

bool Teleportation::UseAbility(Robot& user, Map& map) {
  if (user.GetHealth() <= 0) return false;

  std::cout << "Введите координату x: " << std::endl;
  int x;
  std::cin >> x;

  std::cout << "Введите координату y: " << std::endl;
  int y;
  std::cin >> y;

  if ((x >= 0 && x <= map.GetWidth()) && (y >= 0 && y <= map.GetHeight())) {
    if ((map.GetCell(x, y)->GetCellType() == CellType::kFree) &&
        ((std::abs(user.GetPosX() - x) <= radius_ &&
          std::abs(user.GetPosY() - y) <= radius_))) {
      user.SetPosition(x, y);
      user.ConsumeEnergy(energy_points_);
      return true;
    }
  }
  return false;
}

void Teleportation::UpgradeAbility() {
  if (energy_points_ - energy_cost_decrease_ <= 0) return;
  energy_points_ += energy_cost_decrease_;
}