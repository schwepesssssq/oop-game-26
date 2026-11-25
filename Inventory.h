#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>

class Inventory {
  std::vector<int> inventory_;
  int max_size_ = 4;

 public:
  Inventory() = default;
  std::vector<int>& GetInventory();

  // bool AddItem(int item);
  int GetInventorySize();
  int GetInventoryLimit();
};

#endif