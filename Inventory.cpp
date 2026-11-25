#include "Inventory.h"

std::vector<int>& Inventory::GetInventory() { return inventory_; }
int Inventory::GetInventorySize() { return inventory_.size(); }
int Inventory::GetInventoryLimit() { return max_size_; }