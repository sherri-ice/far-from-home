#include <iostream>
#include "model.h"

Model::Model() {
  Cat main_cat(Size(40, 40), 0.001, Point());
  cats_.push_back(main_cat);
  player_ = std::make_shared<Player>(std::make_shared<Cat>(main_cat));

  for (int i = 0; i < 10; i++) {
    CreateFood();
  }
}

std::shared_ptr<Player> Model::GetPlayer() {
  return player_;
}

std::vector<std::shared_ptr<GameObject>> Model::GetDrawableGameObjects() const {
  std::vector<std::shared_ptr<GameObject>> result;
  for (const auto& cat : player_->GetCats()) {
    result.push_back(cat);
  }
  return result;
}

void Model::LoadLevel(int level) {
  // TODO(anyone)
}

void Model::SetGameState(int) {
  // TODO(anyone)
}

void Model::CreateFood() {
  std::shared_ptr<Food> food = std::make_shared<Food>();
  food_.emplace_back(food);
}

void Model::DeleteFood(const std::shared_ptr<Food>& food) {
      food_.remove(food);
}

void Model::IsFoodNear() {
  for (const auto& player_cat : player_->GetCats()) {
    for (const auto& cur_food : food_) {
      if (player_cat->IsCollision(*cur_food)) {
        DeleteFood(cur_food);
      }
    }
  }
}

std::list<std::shared_ptr<Food>>* Model::GetFood() {
  return &food_;
}
