#include <algorithm>

#include "model.h"

Model::Model() {
  std::shared_ptr<Cat> main_cat = std::make_shared<Cat>(Size(40, 40),
                                                            0.001, Point());
  cats_.emplace_back(main_cat);
  player_ = Player(main_cat);

  std::shared_ptr<Dog> dog = std::make_shared<Dog>(Size(40, 40), 0.00075,
                                                   Point(250, 250), 80);
  dogs_.emplace_back(dog);

  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(789, 65)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(567, 455)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(210, 270)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(25, 500)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(900, 333)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(300, 100)));

  for (auto &food : food_) {
    food->SetScaleCoefficientsInRigidBody(0.9, 0.9);
  }
}

Player* Model::GetPlayer() {
  return &player_;
}

std::vector<std::shared_ptr<GameObject>> Model::GetDrawableGameObjects() const {
  std::vector<std::shared_ptr<GameObject>> result;
  for (const auto& cat : player_.GetCats()) {
    result.push_back(cat);
  }
  for (const auto& dog : dogs_) {
    result.push_back(dog);
  }
  for (const auto& food : food_) {
    result.push_back(food);
  }
  std::sort(result.begin(), result.end(), [](const
  std::shared_ptr<GameObject>& lhs, const std::shared_ptr<GameObject>& rhs) {
    return lhs->GetPosition().GetY() < rhs->GetPosition().GetY();
  });
  return result;
}

void Model::LoadLevel(int level) {
  // TODO(anyone)
}

void Model::SetGameState(int) {
  // TODO(anyone)
}

std::list<std::shared_ptr<Food>> Model::GetFood() {
  return food_;
}

std::list<std::shared_ptr<Dog>> Model::GetDogs() const {
  return dogs_;
}

void Model::ClearObjects() {
  auto it = food_.end();
  --it;
  while (it != food_.begin()) {
    if ((*it)->IsDead()) {
      food_.remove(*it);
    }
    --it;
  }
  if ((*it)->IsDead()) {
    food_.remove(*it);
  }
  auto cat_it = cats_.end();
  --cat_it;
  while (cat_it != cats_.begin()) {
    if ((*cat_it)->IsDead()) {
      cats_.remove(*cat_it);
    }
    --cat_it;
  }
  if ((*cat_it)->IsDead()) {
    cats_.remove(*cat_it);
  }
  auto dog_it = dogs_.end();
  --dog_it;
  while (dog_it != dogs_.begin()) {
    if ((*dog_it)->IsDead()) {
      dogs_.remove(*dog_it);
    }
    --dog_it;
  }
  if ((*dog_it)->IsDead()) {
    dogs_.remove(*dog_it);
  }
}
