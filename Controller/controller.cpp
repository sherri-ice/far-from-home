#include "controller.h"

Controller::Controller() {
  model_ = std::make_shared<Model>();
  view_ = std::make_unique<View>(this, model_);
}

void Controller::Tick(int time) {
  Size player_velocity = view_->GetPlayerVelocity();
  view_->ClearVelocity();
  model_->GetPlayer()->OrderCatsToMove(player_velocity);

  int delta_time = time - current_game_time_;

  for (auto &cat : model_->GetPlayer()->GetCats()) {
    cat->Tick(delta_time);
  }
  for (auto &cat : model_->GetPlayer()->GetCats()) {
    cat->Move(delta_time);
  }
  current_game_time_ = time;
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

void Controller::StartGame(int level) {
  // TODO(anyone)
  // Actually, wanted to start in the center of the screen
  SetPlayerPosition(Point(0, 0));
  model_->LoadLevel(level);
  model_->SetGameState(GameState::kMenu);
}
