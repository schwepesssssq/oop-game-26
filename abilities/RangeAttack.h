#ifndef RANGEATTACK_H
#define RANGEATTACK_H

#include "../utilities/headers/Map.h"
#include "../utilities/headers/Robot.h"
#include "Ability.h"

class RangeAttack : public Ability {
  int range_ = 3;
  int damage_ = 15;
  int energy_cost_ = 10;
  int damage_increase_bonus_ = 10;

 public:
  explicit RangeAttack(int range = 3, int damage = 20);
  bool UseAbility(Robot& user, Map& map) override;
  void UpgradeAbility() override;

  int GetId() const override { return 1; }
  std::string GetName() const override { return "RangeAttack"; }
};

#endif