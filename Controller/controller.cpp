#include "controller.h"

Controller::Controller() {
  model_ = std::make_unique<Model>();
  view_ = std::make_unique<View>(this);
}

void Controller::StartGame(int level) {
  current_game_time_ = 0;
  game_start_time_.start();
  model_->SetModel(level);
}

void Controller::EndGame() {
  model_->ClearGameModel();
  current_game_time_ = 0;
}

void Controller::Tick(int time) {
  current_game_time_ = time;
  GameProcess();
}

void Controller::ClickAction() {
}

void Controller::GameProcess() {
}


void Controller::GenerateFood() {
}

int Controller::GetCurrentTime() {
  return current_game_time_;
}

MovingObject* Controller::GetCat() {
  return model_->GetCat();
}
