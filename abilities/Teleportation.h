#ifndef TELEPORTATION_H
#define TELEPORTATION_H

#include "../utilities/headers/Map.h"
#include "../utilities/headers/Robot.h"
#include "Ability.h"

class Teleportation : public Ability {
  int radius_ = 5;
  int energy_points_ = 20;
  int energy_cost_decrease_ = 5;

 public:
  explicit Teleportation(int radius = 5);
  bool UseAbility(Robot& user, Map& map) override;
  void UpgradeAbility() override;

  int GetId() const override { return 3; }
  std::string GetName() const override { return "Teleportation"; }
};

#endif