#include "Visual.h"

#include <format>
#include <iostream>

#include "Cell.h"
#include "Game.h"
#include "Map.h"
#include "Robot.h"

void Visual::Render(const Game& game) {
  std::system("clear");

  const Map& map = game.GetMap();
  const Robot* player = game.GetPlayer();
  auto robots = game.GetMap().GetRobots();

  if (player) {
    std::cout << std::format(
    "[Move: {}] Player [Rank: {} | Health: {}/{} | Energy: {}/{} | Exp: {}/{} | Speed: {} |Enemies: {}]\n\n",
      game.GetMoveCount(),
      player->GetRank(), player->GetHealth(), player->GetMaxHealth(),
      player->GetEnergy(), player->GetMaxEnergy(),
      player->GetCurrentExperience(), player->GetExperienceToRankUp(),
      player->GetSpeed(), robots.size() - 1);
  }

  for (int y = 0; y < map.GetHeight(); ++y) {
    for (int x = 0; x < map.GetWidth(); ++x) {
      const Cell* cell = map.GetCell(x, y);

      if (cell->IsVisible()) {
        bool robot_flag = false;
        for (auto robot : robots) {
          if (x == robot->GetPositionX() && y == robot->GetPositionY()) {
            if (robot == player) {
              std::cout << "\033[34mP\033[0m ";
            } else {
              std::cout << "\033[31mE\033[0m ";
            }
            robot_flag = 1;
            break;
          }
        }
        if (robot_flag) {
          continue;
        }


        switch (cell->GetCellType()) {
          case CellType::kWall: std::cout << "\033[33m#\033[0m "; break;
          case CellType::kFactory: std::cout << "\033[35mF\033[0m "; break;
          case CellType::kFree: switch (cell->GetMoveCost()) {
            case 1: std::cout << "  "; break;
            default: std::cout << "\033[90m,\033[0m "; break;
          }
        }
      } else {
        if (cell->IsDiscovered()) {
          switch (cell->GetCellType()) {
            case CellType::kWall: std::cout << "\033[90m#\033[0m "; break;
            case CellType::kFactory: std::cout << "\033[90mF\033[0m "; break;
            default: std::cout << "\033[90m?\033[0m "; break;
          }
        } else {
          std::cout << "\033[90m?\033[0m ";
        }
      }
    }
    std::cout << "\n";
  }

  std::cout << "Enter command: ";
}