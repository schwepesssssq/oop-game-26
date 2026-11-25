#ifndef HEALING_H
#define HEALING_H

#include "../utilities/headers/Map.h"
#include "../utilities/headers/Robot.h"
#include "Ability.h"

class Healing : public Ability {
  int healing_ = 25;
  int energy_cost_ = 15;
  int healing_increase_bonus_ = 10;

 public:
  explicit Healing(int healing_points = 25);
  bool UseAbility(Robot& user, Map& map) override;
  void UpgradeAbility() override;

  int GetId() const override { return 2; }
  std::string GetName() const override { return "Healing"; }
};

#endif