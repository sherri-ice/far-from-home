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
  TickViewCircle();

  model_->ClearObjects();
}

int Controller::GetCurrentTime() {
  return current_game_time_;
}

void Controller::StartGame() {
  current_game_time_ = 0;
  window_type_ = WindowType::kGame;
  view_->DisableMainMenuUi();
  view_->EnableGameUi();
  model_->SetGameState(GameState::kGame);
}

Player* Controller::GetPlayer() {
  return model_->GetPlayer();
}

void Controller::TickPlayer() {
  Size player_velocity = view_->GetPlayerVelocity();
  auto player = model_->GetPlayer();
  view_->ClearVelocity();
  player->OrderCatsToMove(player_velocity);
  player->UpdateDogsAround(model_->GetDogs());
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
    for (auto& cat : player->GetCats()) {
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

void Controller::TickViewCircle() {
  double player_view = view_->GetViewSize();
  auto view_circle = GetPlayer()->GetViewCircle();
  Point bg = GetPlayer()->GetPosition();

  view_circle.SetCenter(GetPlayer()->GetPosition());
  view_circle.SetWantedRadius(player_view);
  model_->GetPlayer()->SetViewCircle(view_circle);
  GetPlayer()->Tick();
  view_->UpdateResizer(GetPlayer()->GetViewCircle().GetRadius(),
                       GetPlayer()->GetPosition());
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

void Controller::SecondConstructorPart() {
  model_->SetModel();
  view_->SecondConstructorPart();
  map_generator_.SetModel(model_);
  map_generator_.GenerateMap();
}
QPixmap Controller::GetBackground(WindowType type) const {
  return model_->GetBackground(static_cast<int>(type));
}

//todo doesnt restart game
void Controller::EndGame() {
  model_->ClearObjects();
  view_->DisableGameUi();
  view_->EnableMainMenuUi();
  window_type_ = WindowType::kMainMenu;
  current_game_time_ = 0;
  model_->SetGameState(GameState::kMenu);
  // music_player_.StartMenuMusic();
}
