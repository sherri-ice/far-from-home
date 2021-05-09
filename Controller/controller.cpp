#include "controller.h"

Controller::Controller() {
  model_ = std::make_shared<Model>();
  view_ = std::make_shared<View>(this, model_);
}

void Controller::Tick(int time) {
  int delta_time = time - current_game_time_;
  double player_view = view_->GetViewSize();
  auto view_circle = GetPlayer()->GetViewCircle();
  view_circle.SetCenter(GetPlayer()->GetPosition());
  view_circle.SetWantedRadius(player_view);
  model_->GetPlayer()->SetViewCircle(view_circle);
  GetPlayer()->Tick();
  view_->UpdateResizer(GetPlayer()->GetViewCircle().GetRadius(),
                       GetPlayer()->GetPosition());
  current_game_time_ = time;

  TickPlayer(delta_time);
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

Player* Controller::GetPlayer() {
  return model_->GetPlayer();
}

void Controller::TickPlayer(int delta_time) {
  Size player_velocity = view_->GetPlayerVelocity();
  auto player = model_->GetPlayer();
  view_->ClearVelocity();
  player->IsReachable(model_->GetDogs());
  player->UpdateCatsGroup(model_->GetCats());
  player->OrderCatsToMove(player_velocity);
  player->UpdateDogsAround(model_->GetDogs());
  player->GroupTick(delta_time);
}

void Controller::TickCats(int time) {
  for (auto& cat : model_->GetCats()) {
    cat->Tick(time);
    cat->Move(time);
  }
}

void Controller::TickDogs(int delta_time) {
  std::list<std::shared_ptr<Dog>> dogs = model_->GetDogs();
  auto player = model_->GetPlayer();
  for (auto& dog : dogs) {
    dog->SetReachableCat(player->GetCats());
    dog->Tick(delta_time);
    dog->Move(delta_time);
    for (auto &cat : player->GetCats()) {
      if (dog->GetRigidBody().IsCollide(cat->GetRigidBody())) {
        if (cat == player->GetMainCat()) {
          player->DismissCats();
          // dog->SetDogState(DogState::IsComingHome);
          break;
        } else {
          player->LosingCat(dog->GetRigidPosition(), cat);
        }
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
