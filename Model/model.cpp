#include <algorithm>

#include "Model/model.h"
#include "View/progress_bar.h"

Model::Model() {
  std::shared_ptr<Cat> main_cat = std::make_shared<Cat>(Size(40, 40),
                                                        10,
                                                        Point(0, 0));
  cats_.emplace_back(main_cat);
  for (auto& food : food_) {
    food->SetScaleCoefficientsInRigidBody(0.9, 0.9);
  }
  player_ = new Player(main_cat);

  // Temporary
  MakeNewPortal(Size(60, 60), Point(0, 100), "", true);
  MakeNewPortal(Size(60, 60), Point(200, 100), "", true);
  MakeNewPortal(Size(60, 60), Point(200, 120), "", true);
  MakeNewPortal(Size(60, 60), Point(200, 140), "", true);
  MakeNewPortal(Size(60, 60), Point(100, 10), "", true);
  MakeNewPortal(Size(60, 60), Point(350, -20), "", true);
  MakeNewPortal(Size(60, 60), Point(-100, 100), "", true);

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
  for (const auto& static_object : static_objects_) {
    result.push_back(static_object);
  }
  for (const auto& warning : warnings_) {
    result.push_back(warning);
  }
  std::sort(result.begin(), result.end(), [](const
                                             std::shared_ptr<GameObject>& lhs,

                                             const std::shared_ptr<GameObject>&
                                             rhs) {
    return lhs->GetDrawPosition().GetY() < rhs->GetDrawPosition().GetY();
  });
  return result;
}

std::shared_ptr<Cat> Model::MakeNewCat(const Size& size,
                                       double speed,
                                       const Point& point) {
  cats_.push_back(std::make_shared<Cat>(size, speed, point));
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

  for (auto it = warnings_.rbegin(); it != warnings_.rend(); ++it) {
    if ((*it)->IsDead()) {
      warnings_.remove(*it);
    }
  }
}


std::list<std::shared_ptr<PortalObject>>& Model::GetStaticObjects() {
  return static_objects_;
}

std::shared_ptr<PortalObject> Model::MakeNewPortal(const Size& size,
                                                   const Point& position,
                                                   const QString& skin_path,
                                                   bool has_portal) {
  static_objects_.push_back(std::make_shared<PortalObject>(size,
                                                           position,
                                                           skin_path));
  if (has_portal) {
    static_objects_.back()->SetPortal();
  }
  return static_objects_.back();
}

void Model::AddWarning(const std::shared_ptr<Warning>& warning) {
  warnings_.emplace_back(warning);
}

std::vector<std::shared_ptr<Warning>> Model::GetWarnings() {
  std::vector<std::shared_ptr<Warning>> result;
  for (const auto& warning : warnings_) {
    result.push_back(warning);
  }
  return result;
}

std::shared_ptr<Dog> Model::MakeNewDog(const Size& size,
                                       double speed,
                                       const Point& point,
                                       double visibility_radius,
                                       double waking_speed) {
  dogs_.push_back(std::make_shared<Dog>(size,
                                        speed,
                                        point,
                                        visibility_radius,
                                        waking_speed));
  return dogs_.back();
}

std::shared_ptr<Food> Model::MakeNewFood(const Size& size, const Point& point) {
  food_.push_back(std::make_shared<Food>(size, point));
  return food_.back();
}


