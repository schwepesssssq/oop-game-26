#ifndef AOEATTACK_H
#define AOEATTACK_H

#include "../utilities/headers/Map.h"
#include "../utilities/headers/Robot.h"
#include "Ability.h"

class AoEAttack : public Ability {
  int radius_ = 1;
  int damage_ = 25;
  int energy_cost_ = 20;
  int upgrade_area_ = 1;

 public:
  explicit AoEAttack(int radius = 1, int damage = 25);
  bool UseAbility(Robot& user, Map& map) override;
  void UpgradeAbility() override;

  int GetId() const override { return 0; }
  std::string GetName() const override { return "AoE Attack"; }
};

#endif