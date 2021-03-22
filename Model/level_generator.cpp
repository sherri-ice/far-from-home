#include "level_generator.h"

LevelGenerator::LevelGenerator(int level) : current_level_(level) {
  switch (level) {
    case 0: {
      max_number_of_cats_at_level_ = 0;
      player_speed_ = 0.001;
      visibility_radius_ = 20;
      break;
    }
    default: {
      break;
    }
  }
}

void LevelGenerator::GenerateLevel(int level) {
  current_level_ = level;
  switch (level) {
    case 0: {
      max_number_of_cats_at_level_ = 0;
      player_speed_ = 0.001;
      visibility_radius_ = 20;
      break;
    }
    default: {
      break;
    }
  }
}

double LevelGenerator::GetPlayerSpeed() const {
  return player_speed_;
}
