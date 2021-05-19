#include "controller.h"

Controller::Controller() {
  music_player_ = std::make_shared<MusicPlayer>();
  model_ = std::make_shared<Model>();
  view_ = std::make_shared<View>(this, model_);
  // map_generator_.SetModel(model_);
  // map_generator_.GenerateMap();
  music_player_->StartMenuMusic();
}

void Controller::Tick(int time) {
  int delta_time = time - current_game_time_;
  current_game_time_ = time;

  TickPlayer(delta_time);
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
  model_->SetModel();
  map_generator_.SetModel(model_);
  map_generator_.GenerateMap();
  view_->SetIsPaused(false);
  current_game_time_ = 0;
  music_player_->StartGameMusic();
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
    for (auto& cat : player->GetCats()) {
      if (dog->GetRigidBody().IsCollide(cat->GetRigidBody())) {
        if (cat == player->GetMainCat()) {
          player->DismissCats();
          dog->SetIsMainCatCaught(true);
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

void Controller::TickViewCircle() {
  double player_view = view_->GetViewSize();
  auto view_circle = GetPlayer()->GetViewCircle();
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

void Controller::EndGame() {
  model_->ClearModel();
  view_->SetIsPaused(true);
  current_game_time_ = 0;
  music_player_->StartMenuMusic();
}
void Controller::SetGameVolume(int volume) {
  music_player_->SetVolume(volume);
  // model_->SetParticlesVolume(volume);
}
std::shared_ptr<MusicPlayer> Controller::GetMusicPlayer() {
  return music_player_;
}
void Controller::PauseMusic() {
  music_player_->Pause();
}
void Controller::ResumeMusic() {
  music_player_->Resume();
}

