#include "model.h"

Model::Model() {
  Cat main_cat(Size(40, 40), 0.001, Point());
  auto main_cat_ptr = std::make_shared<Cat>(main_cat);
  cats_.push_back(main_cat_ptr);
  player_ = new Player(main_cat_ptr);
}

Player* Model::GetPlayer() {
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

void Model::RescaleObjects(const Resizer& resizer) {
    for (auto& cat : cats_) {
      cat->Resize(resizer.GameToWindowSize(cat->GetSize()));
    }
}
