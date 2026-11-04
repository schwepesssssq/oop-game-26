#include "Controller.h"

#include <cctype>
#include <iostream>

#include "Game.h"
#include "Move.h"
#include "Visual.h"

Controller::Controller(Game& game) : game_(game) {}

void Controller::Run() {
  while (game_.GetState() == GameState::kInProgress) {
    Visual::Render(game_);

    if (!ProcessInput()) {
      std::cout << "Game exited by user.\n";
      return;
    }
  }

  Visual::Render(game_);
  if (game_.GetState() == GameState::kPlayerWon) {
    std::cout << "\nYou win!\n";
  } else if (game_.GetState() == GameState::kPlayerLost) {
    std::cout << "\nYou lose!\n";
  }
}

bool Controller::ProcessInput() {
  std::string input;
  std::cin >> input;

  if (input.length() != 1) {
    return true;
  }

  Direction direction;
  switch (std::tolower(input[0])) {
    case 'w':
      direction = Direction::kUp;
      break;
    case 's':
      direction = Direction::kDown;
      break;
    case 'a':
      direction = Direction::kLeft;
      break;
    case 'd':
      direction = Direction::kRight;
      break;
    case 'q':
      return false;
    default:
      return true;
  }

  game_.PlayerMove(direction);
  return true;
}
