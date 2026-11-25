#include "Cell.h"

#include <algorithm>

Cell::Cell(CellType type, int move_cost)
    : type_(type), move_cost_(std::max(1, move_cost)), is_discovered_(false) {}

CellType Cell::GetCellType() const { return type_; }

int Cell::GetMoveCost() const { return move_cost_; }

bool Cell::IsDiscovered() const { return is_discovered_; }
bool Cell::IsVisible() const { return is_visible_; }

void Cell::SetCellType(CellType type) { type_ = type; }

void Cell::SetMoveCost(int cost) { move_cost_ = std::max(1, cost); }

void Cell::SetDiscovered(bool discovered) { is_discovered_ = discovered; }

void Cell::SetVisible(bool visible) {
  is_visible_ = visible;
  if (visible) {
    is_discovered_ = true;
  }
}