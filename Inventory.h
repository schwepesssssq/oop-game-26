#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>

#include "abilities/Ability.h"

class Inventory {
 private:
  std::vector<std::unique_ptr<Ability>> inventory_;
  int max_size_ = 4;

 public:
  Inventory() = default;

  bool AddAbility(std::unique_ptr<Ability> ability);

  Ability* GetAbility(int index);
  const Ability* GetAbility(int index) const;

  int GetInventorySize() const;
  int GetInventoryLimit() const;
};

#endif