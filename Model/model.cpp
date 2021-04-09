#include "model.h"

Model::Model() {
  Cat main_cat(Size(40, 40), 0.001, Point());
  auto main_cat_ptr = std::make_shared<Cat>(main_cat);
  cats_.push_back(main_cat_ptr);
  player_ = new Player(main_cat_ptr);
  // Temporary
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


