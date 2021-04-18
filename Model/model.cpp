#include <algorithm>

#include "model.h"

#include <QDebug>

Model::Model() {
  Point central_pos =
      Point(constants::kGameMapWidth / 2, constants::kGameMapHeight / 2);
  std::shared_ptr<Cat> main_cat = std::make_shared<Cat>(constants::kCatSize,
                                                        0.001, central_pos);
  map_.cats_.emplace_back(main_cat);

  // for (auto &food : food_) {
  //   food->SetScaleCoefficientsInRigidBody(0.9, 0.9);
  // }

  player_ = new Player(main_cat);

  player_->SetViewCircle(ViewCircle(player_->GetPosition(),
                                    constants::kViewCircleDefault));
}

Player* Model::GetPlayer() {
  return player_;
}

std::vector<std::shared_ptr<GameObject>> Model::GetDrawableGameObjects() const {
  std::vector<std::shared_ptr<GameObject>> result;
  for (const auto& cat : map_.cats_) {
    result.push_back(cat);
  }
  for (const auto& dog : map_.dogs_) {
    result.push_back(dog);
  }
  for (const auto& food : map_.food_) {
    result.push_back(food);
  }
  std::sort(result.begin(), result.end(), [](const
                                             std::shared_ptr<GameObject>& lhs,
                                             const std::shared_ptr<GameObject>&
                                             rhs) {
    return lhs->GetDrawPosition().GetY() < rhs->GetDrawPosition().GetY();
  });
  return result;
}

void Model::SetGameState(int) {
  // TODO(anyone)
}

std::list<std::shared_ptr<Food>> Model::GetFood() {
  return map_.food_;
}

std::list<std::shared_ptr<Dog>> Model::GetDogs() {
  return map_.dogs_;
}

std::list<std::shared_ptr<Cat>> Model::GetCats() {
  return map_.cats_;
}

void Model::ClearObjects() {
  for (auto it = map_.food_.rbegin(); it != map_.food_.rend(); ++it) {
    if ((*it)->IsDead()) {
      map_.food_.remove(*it);
    }
  }

  for (auto it = map_.cats_.rbegin(); it != map_.cats_.rend(); ++it) {
    if ((*it)->IsDead()) {
      map_.cats_.remove(*it);
    }
  }

  for (auto it = map_.dogs_.rbegin(); it != map_.dogs_.rend(); ++it) {
    if ((*it)->IsDead()) {
      map_.dogs_.remove(*it);
    }
  }
}

void Model::LoadMap() {
  map_.MakeMap();
}
