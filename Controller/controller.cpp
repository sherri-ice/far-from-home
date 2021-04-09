#include "controller.h"

Controller::Controller() {
  model_ = std::make_shared<Model>();
  view_ = std::make_shared<View>(this, model_);
}

void Controller::Tick(int time) {
  Size player_velocity = view_->GetPlayerVelocity();
  view_->ClearVelocity();
  model_->GetPlayer()->OrderCatsToMove(player_velocity);

  double player_view = view_->GetViewSize();
  auto view_circle = GetPlayer()->GetViewCircle();
  view_circle.SetWantedRadius(player_view);
  model_->GetPlayer()->SetViewCircle(view_circle);
  GetPlayer()->Tick();
  view_->UpdateResizer(GetPlayer()->GetViewCircle().GetRadius(),
                       GetPlayer()->GetPosition());
  int delta_time = time - current_game_time_;
  for (auto& cat : model_->GetPlayer()->GetCats()) {
    cat->Tick(delta_time);
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

void Controller::StartGame(int level) {
  // TODO(anyone)
  // Actually, wanted to start in the center of the screen
  SetPlayerPosition(Point(0, 0));
  model_->LoadLevel(level);
  model_->SetGameState(GameState::kMenu);
}




