#include "controller.h"

Controller::Controller() {
  model_ = std::make_shared<Model>();
  view_ = std::make_shared<View>(this, model_);
}

void Controller::Tick(int time) {
  Size player_velocity = view_->GetPlayerVelocity();
  view_->ClearVelocity();
}

Player* Controller::GetPlayer() {
  return model_->GetPlayer();
}

void Controller::SetPlayerPosition(const Point& position) {
  for (auto& cat : model_->GetPlayer()->GetCats()) {
    cat->SetPosition(position);
  }
}

int Controller::GetCurrentTime() {
  return current_game_time_;
}

Cat* Controller::MakeCat() {
  auto new_cat = model_->MakeCat();
  return new_cat;
}

void Controller::StartGame() {
  // TODO(anyone)
  // Actually, wanted to start in the center of the screen
  SetPlayerPosition(Point(0, 0));
  model_->SetGameState(GameState::kMenu);
}


