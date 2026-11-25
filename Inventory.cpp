#include "Inventory.h"

bool Inventory::AddAbility(std::unique_ptr<Ability> ability) {
  if (inventory_.size() >= max_size_) return false;
  inventory_.push_back(std::move(ability));
  return true;
}

Ability* Inventory::GetAbility(int index) {
  if (index < 0 || index >= static_cast<int>(inventory_.size())) return nullptr;
  return inventory_[index].get();
}

const Ability* Inventory::GetAbility(int index) const {
  if (index < 0 || index >= static_cast<int>(inventory_.size())) return nullptr;
  return inventory_[index].get();
}

int Inventory::GetInventorySize() const { return inventory_.size(); }
int Inventory::GetInventoryLimit() const { return max_size_; }