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

  TickPlayer();
  TickCats(delta_time);
  TickDogs(delta_time);
  TickFood(delta_time);
  TickObjects(delta_time);

  CatsAndFoodIntersect();

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

void Controller::TickPlayer() {
  Size player_velocity = view_->GetPlayerVelocity();
  auto player = model_->GetPlayer();
  view_->ClearVelocity();
  player->OrderCatsToMove(player_velocity);
  player->UpdateDogsAround(model_->GetDogs());
}

void Controller::TickCats(int delta_time) {
  for (auto& cat : model_->GetPlayer()->GetCats()) {
    cat->Tick(delta_time);
    MovingAndStaticObjectsIntersect(cat);
    cat->Move(delta_time);
  }
}

void Controller::TickDogs(int delta_time) {
  std::list<std::shared_ptr<Dog>> dogs = model_->GetDogs();
  auto player = model_->GetPlayer();
  for (auto& dog : dogs) {
    dog->SetReachableCat(player->GetCats());
    dog->Tick(delta_time);
    MovingAndStaticObjectsIntersect(dog);
    dog->Move(delta_time);
    for (auto &cat : player->GetCats()) {
      if (dog->GetRigidBody()->IsCollide(*(cat->GetRigidBody()))) {
        player->DismissCats();
        break;
      }
    }
  }
}

void Controller::TickFood(int delta_time) {
  // Food rots
}

void Controller::CatsAndFoodIntersect() {
  for (const auto& player_cat : model_->GetPlayer()->GetCats()) {
    for (auto& food : model_->GetFood()) {
      if (player_cat->GetRigidBody()->IsCollide(*(food->GetRigidBody()))) {
        food->SetIsDead();
      }
    }
  }
}

void Controller::TickObjects(int time) {
  for (auto& object : model_->GetStaticObjects()) {
    object->Tick(time);
  }
  for (auto& object : model_->GetStaticObjects()) {
    // if (object->IsSearchComplete()) {
    // }
  }
}

void Controller::MovingAndStaticObjectsIntersect(const
std::shared_ptr<MovingObject>& moving_object) {
  for (const auto& static_object : model_->GetStaticObjects()) {
    if (moving_object->GetRigidBody()->IfCollisionWillHappen(*(static_object->GetRigidBody
    ()), moving_object->GetVelocity())) {
      Size new_velocity = moving_object->GetRigidBody()->GetVelocityToAvoidCollision
          (*(static_object->GetRigidBody()), moving_object->GetVelocity());
      moving_object->SetVelocity(new_velocity * moving_object->GetVelocity().GetLength());
    }
  }
}

void Controller::ScanIfObjectWereClicked(const Point& point) {
  for (const auto& object : model_->GetStaticObjects()) {
    if (object->GetDrawPosition().IsInEllipse(point, 100)) {
      if (!object->IsSearchComplete()) {
        object->SetSearchState();
      }
    }
  }
}
