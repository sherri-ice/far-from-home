#include "model.h"

Model::Model() {
  Cat main_cat(Size(40, 40), 0.001, Point());
  cats_.push_back(main_cat);
  player_ = std::make_shared<Player>(std::make_shared<Cat>(main_cat));
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
