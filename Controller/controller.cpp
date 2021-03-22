#include "controller.h"

Controller::Controller() {
  model_ = std::make_unique<Model>();
  view_ = std::make_unique<View>(this);
}

void Controller::Tick(int time) {
  Size player_velocity = view_->GetPlayerVelocity();
  view_->ClearVelocity();
  model_->GetPlayer()->SetVelocity(player_velocity);
  int delta_time = time - current_game_time_;
  model_->GetPlayer()->Tick(delta_time);
  model_->GetPlayer()->Move(delta_time);
  current_game_time_ = time;
}

MovingObject* Controller::GetPlayer() {
  return model_->GetPlayer();
}

void Controller::SetPlayerPosition(Point position) {
  model_->SetPlayerPosition(position);
}

int Controller::GetCurrentTime() {
  return current_game_time_;
}


