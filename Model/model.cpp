#include "model.h"

Model::Model() {
  auto main_cat = MakeCat();
  player_ = new Player(main_cat);
}

Player* Model::GetPlayer() {
  return player_;
}

std::vector<GameObject*> Model::GetDrawableGameObjects() const {
  std::vector<GameObject*> result;
  for (const auto& cat : player_->GetCats()) {
    result.push_back(cat);
  }
  return result;
}

Cat* Model::MakeCat() {
  Cat new_cat(Size(40, 40), 0.001, Point());
  cats_.push_back(new_cat);
  return &cats_.at(0);
}

void Model::LoadLevel(int level) {
  // TODO(anyone)
}

void Model::SetGameState(int) {
  // TODO(anyone)
}
