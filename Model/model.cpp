#include <algorithm>

#include "model.h"

Model::Model() {
  std::shared_ptr<Cat> main_cat = std::make_shared<Cat>(Size(40, 40),
                                                            0.001, Point());
  main_cat->SetIsInGroup(true);
  cats_.emplace_back(main_cat);

  std::shared_ptr<Dog> dog = std::make_shared<Dog>(Size(40, 40), 0.00075,
                                                   Point(250, 250), 100);
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

  player_ = new Player(main_cat);
  // Temporary
  MakeNewCat(Size(20, 20), 0.0005, Point(50, 0));
  MakeNewCat(Size(40, 40), 0.001, Point(50, 50));

  player_->SetViewCircle(ViewCircle(player_->GetPosition(),
                                    constants::kViewCircleDefault));
}

Player* Model::GetPlayer() {
  return player_;
}

std::vector<std::shared_ptr<GameObject>> Model::GetDrawableGameObjects() const {
  std::vector<std::shared_ptr<GameObject>> result;
  for (const auto& cat : cats_) {
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
    return lhs->GetDrawPosition().GetY() < rhs->GetDrawPosition().GetY();
  });
  return result;
}

std::shared_ptr<Cat> Model::MakeNewCat(const Size& size,
                                       double speed,
                                       const Point& point) {
  std::shared_ptr<Cat> new_cat = std::make_shared<Cat>(size, speed, point);
  cats_.push_back(new_cat);
  return cats_.back();
}

void Model::LoadLevel(int level) {
  // TODO(anyone)
}

void Model::SetGameState(int) {
  // TODO(anyone)
}

std::list<std::shared_ptr<Food>> Model::GetFood() const {
  return food_;
}

std::list<std::shared_ptr<Dog>> Model::GetDogs() const {
  return dogs_;
}

std::list<std::shared_ptr<Cat>> Model::GetCats() const {
  return cats_;
}

void Model::ClearObjects() {
  for (auto it = food_.rbegin(); it != food_.rend(); ++it) {
    if ((*it)->IsDead()) {
          food_.remove(*it);
        }
  }

  for (auto it = cats_.rbegin(); it != cats_.rend(); ++it) {
    if ((*it)->IsDead()) {
      cats_.remove(*it);
    }
  }

  for (auto it = dogs_.rbegin(); it != dogs_.rend(); ++it) {
    if ((*it)->IsDead()) {
      dogs_.remove(*it);
    }
  }
}
