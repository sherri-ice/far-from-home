#include <algorithm>
#include <View/progress_bar.h>

#include "model.h"

Model::Model() {
  std::shared_ptr<Cat> main_cat = std::make_shared<Cat>(Size(40, 40),
                                                        10, Point());
  cats_.emplace_back(main_cat);

  std::shared_ptr<Dog> dog = std::make_shared<Dog>(Size(40, 40), 7.5,
                                                   Point(250, 250),
                                                   100, 1.75);
  dogs_.emplace_back(dog);

  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(789, 65)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(567, 455)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(210, 270)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(25, 500)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(900, 333)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(300, 100)));

  for (auto& food : food_) {
    food->SetScaleCoefficientsInRigidBody(0.9, 0.9);
  }

  player_ = new Player(main_cat);
  // Temporary
  MakeNewPortal(Size(60, 60), Point(0, 0), "");
  MakeNewCat(Size(60, 60), 0.001, Point(1000, 0));
  MakeNewCat(Size(10, 10), 0.001, Point(500, 500));
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
  for (const auto& object : objects_) {
    result.push_back(object);
  }
  std::sort(result.begin(), result.end(), [](const
                                             std::shared_ptr<GameObject>& lhs,
                                             const std::shared_ptr<GameObject>& rhs) {
    return lhs->GetDrawPosition().GetY() < rhs->GetDrawPosition().GetY();
  });
  return result;
}

std::shared_ptr<Cat> Model::MakeNewCat(const Size& size,
                                       double speed,
                                       const Point& point) {
  Cat new_cat(size, speed, point);
  auto new_cat_ptr = std::make_shared<Cat>(new_cat);
  cats_.push_back(new_cat_ptr);
  return cats_.back();
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

std::list<std::shared_ptr<Dog>> Model::GetDogs() {
  return dogs_;
}

std::list<std::shared_ptr<Cat>> Model::GetCats() {
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

std::list<std::shared_ptr<PortalObject>>& Model::GetObjects() {
  return objects_;
}

std::shared_ptr<PortalObject> Model::MakeNewPortal(const Size& size,
                                                   const Point& position,
                                                   const QString& skin_path) {
  objects_.push_back(std::make_shared<PortalObject>(size, position, skin_path));
  return objects_.back();
}
