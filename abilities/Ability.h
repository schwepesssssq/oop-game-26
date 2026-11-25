#ifndef ABILITY_H
#define ABILITY_H
#include <iostream>

class Map;
class Robot;

enum class Abilities {
  kAoEAttack,     // 0
  kRangeAttack,   // 1
  kHealing,       // 2
  kTeleportation  // 3
};

class Ability {
 public:
  virtual ~Ability() = default;
  virtual bool UseAbility(Robot& user, Map& map) = 0;
  virtual void UpgradeAbility() = 0;

  virtual int GetId() const = 0;
  virtual std::string GetName() const = 0;
};

#endif