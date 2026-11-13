#ifndef CELL_H
#define CELL_H

enum class CellType {
  kWall,
  kFree,
  kFactory,
};

class Cell {
 public:
  Cell(CellType type, int move_cost);

  CellType GetCellType() const;
  int GetMoveCost() const;
  bool IsDiscovered() const;
  bool IsVisible() const;
  void SetDiscovered(bool discovered);
  void SetVisible(bool visible);

  void SetCellType(CellType type);
  void SetMoveCost(int cost);
  
 private:
  CellType type_;
  int move_cost_;        
  bool is_discovered_;
  bool is_visible_;
};

#endif