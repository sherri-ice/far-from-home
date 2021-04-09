#include "controller.h"

Controller::Controller() {
  model_ = std::make_shared<Model>();
  view_ = std::make_shared<View>(this, model_);
}

void Controller::Tick(int time) {
  int delta_time = time - current_game_time_;
  current_game_time_ = time;

  TickPlayer();
  TickCats(delta_time);
  TickDogs(delta_time);
  CatsAndFoodIntersect();
  TickFood(delta_time);

  model_->ClearObjects();
}

int Controller::GetCurrentTime() {
  return current_game_time_;
}

void Controller::StartGame(int level) {
  // TODO(anyone)
  // Actually, wanted to start in the center of the screen
  model_->LoadLevel(level);
  model_->SetGameState(GameState::kMenu);
}

void Controller::TickPlayer() {
  Size player_velocity = view_->GetPlayerVelocity();
  view_->ClearVelocity();
  model_->GetPlayer()->OrderCatsToMove(player_velocity);
}

void Controller::TickCats(int time) {
  for (auto &cat : model_->GetPlayer()->GetCats()) {
    cat->Tick(time);
    cat->Move(time);
  }
}

void Controller::TickDogs(int time) {
  std::list<std::shared_ptr<Dog>> dogs = model_->GetDogs();
  auto* player = model_->GetPlayer();
  player->CheckForDogsAround(dogs);
  Point player_position = player->GetCentralCatPosition();
  double group_radius = player->GetGroupRadius();
  for (auto &dog : dogs) {
    bool can_see = dog->CheckIfCanSeePlayer(player_position, group_radius);
    if (can_see) {
      dog->SetDestination(player_position);
    } else {
      dog->SetDestination(dog->GetHomePosition());
    }
    dog->Tick(time);
    dog->Move(time);
    for (auto &cat : player->GetCats()) {
      if (dog->GetRigidBody().IsCollide(cat->GetRigidBody())) {
        player->DismissCats();
        break;
      }
    }
  }
}

void Controller::TickFood(int time) {
  // Food rots
}

void Controller::CatsAndFoodIntersect() {
  for (const auto& player_cat : model_->GetPlayer()->GetCats()) {
    for (auto& food : model_->GetFood()) {
      if (player_cat->GetRigidBody().IsCollide(food->GetRigidBody())) {
        food->SetIsDead();
      }
    }
  }
}
