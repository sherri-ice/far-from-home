#include "controller.h"

Controller::Controller() {
  music_player_ = std::make_shared<MusicPlayer>();
  model_ = std::make_shared<Model>();
  view_ = std::make_shared<View>(this, model_);
  map_generator_.SetModel(model_);
  map_generator_.GenerateMap();
}

void Controller::Tick(int time) {
  int delta_time = time - current_game_time_;
  current_game_time_ = time;

  // TickViewCircle();
  TickPlayer(delta_time);
  TickCats(delta_time);
  TickDogs(delta_time);
  TickFood(delta_time);
  TickObjects(delta_time);
  TickWarnings(delta_time);
  CatsAndFoodIntersect();
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
  player->UpdateStaticObjectsAround(model_->GetStaticObjects());
  player->GroupTick(delta_time);
}

void Controller::TickCats(int delta_time) {
  for (auto& cat : model_->GetCats()) {
    if (view_->IsOnTheScreen(cat)) {
      for (auto& dog : model_->GetDogs()) {
        if (cat->GetCatState() == CatState::kIsWalking
            && cat->GetRigidPosition().
                GetVectorTo(dog->GetRigidPosition()).GetLength() <
                dog->GetVisibilityRadius()) {
          cat->ComeHome();
        }
      }
        cat->Tick(delta_time);
        MovingAndStaticObjectsIntersect(cat);
        CatsAndPortalsIntersect(cat);
        cat->Move(delta_time);
      }
    }
}

void Controller::TickDogs(int delta_time) {
  std::list<std::shared_ptr<Dog>> dogs = model_->GetDogs();
  auto player = model_->GetPlayer();
  for (auto& dog : dogs) {
    dog->SetReachableCat(player->GetCats());
    for (auto& cat : player->GetCats()) {
      if (dog->GetRigidBody()->IsCollide(*(cat->GetRigidBody()))) {
        if (cat->GetRigidPosition().
            GetVectorTo(dog->GetRigidPosition()).GetLength() <
            dog->GetVisibilityRadius() && player->GetCats().size() >
            dog->GetNumOfCatsToRunAway()) {
          dog->RunAway(cat->GetRigidPosition());
          break;
        }
        if (dog->GetRigidBody()->IsCollide(*cat->GetRigidBody())) {
          if (cat == player->GetMainCat()) {
            player->DismissCats();
            dog->SetIsMainCatCaught(true);
            break;
          } else if (cat->GetCatState() != CatState::kIsSearching) {
            player->LosingCat(dog->GetRigidPosition(), cat);
          } else if (cat->GetCatState() == CatState::kIsSearching
              || cat->GetCatState() == CatState::kIsGoingToSearch) {
            dog->ComeHome();
          }
        }
      }
      for (auto& wild_cat : model_->GetCats()) {
        if (!wild_cat->GetIsInGroup() &&
            dog->GetDogState() == DogState::kIsWalking &&
            dog->GetRigidPosition().GetVectorTo(wild_cat->GetRigidPosition()).
                GetLength() < dog->GetVisibilityRadius()) {
          dog->ComeHome();
        }
      }
      dog->Tick(delta_time);
      dog->Move(delta_time);
    }
  }
}

void Controller::TickFood(int delta_time) {
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
      if (player_cat->GetRigidBody()->IsCollide(*(food->GetRigidBody()))) {
        food->SetIsDead();
      }
    }
  }
}

void Controller::EndGame() {
  model_->ClearModel();
  current_game_time_ = 0;
  // music_player_->StartMenuMusic();
}
void Controller::SetGameVolume(int volume) {
  music_player_->SetVolume(volume);
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


void Controller::TickObjects(int delta_time) {
  for (auto& object : model_->GetStaticObjects()) {
    object->Tick(delta_time);
    if (object->HasFinished()) {
      model_->AddWarning(std::make_shared<Warning>("Search is "
                                                   "finished. Come back to the "
                                                   "tree to see the result",
                                                   view_->
                                                       GetCoordinatesForWarning
                                                       (),
                                                   32, true,
                                                   true, 3000));
      object->SetWaitState();
    }
  }
}

void Controller::MovingAndStaticObjectsIntersect(const
                                                 std::shared_ptr<MovingObject>&
moving_object) {
  for (const auto& static_object : model_->GetStaticObjects()) {
    if (moving_object->
        GetRigidBody()->IfCollisionWillHappen(*(static_object->GetRigidBody()),
                                              moving_object->GetVelocity())) {
      Size new_velocity = moving_object->GetRigidBody()
          ->GetVelocityToAvoidCollision(*(static_object->GetRigidBody()),
                                        moving_object->GetVelocity());
      moving_object->SetVelocity(new_velocity * moving_object->GetVelocity()
          .GetLength());
    }
  }
}

void Controller::ScanIfObjectWereClicked(const Point& point) {
  for (auto& object : model_->GetStaticObjects()) {
    if (object->GetDrawPosition().IsInEllipse(point,
                                              object->GetSize().GetLength())) {
      if (object->HasFinished()) {
        view_->ShowResultWindow(object->HasPortal());
        int i;
        while (!view_->GetResultWindow().isHidden()) {
          i++;
        }
        if (view_->GetResultWindow().GetUserAnswer()) {
          portal_and_searching_cat_[object]->SetCatState
          (CatState::kNeedsToBeSendHome);
        } else {
          portal_and_searching_cat_[object]->SetCatState
              (CatState::kIsFollowingPlayer);
        }
        object->SetCollectedState();
        continue;
      }
      if (!object->IsCollected()
          && model_->GetPlayer()->NotOnlyMainCat()) {
        auto cat =
            model_->GetPlayer()->SendCatToSearch(
                object->GetDrawPosition()
                    + Point(0, object->GetSize().GetHeight() / 2),
                object->GetSearchTime());
        portal_and_searching_cat_[object] = cat;
      } else if (object->IsCollected()) {
        model_->AddWarning(std::make_shared<Warning>(
            "You've already searched a portal here!",
            view_->
                GetCoordinatesForWarning(),
            32,
            true,
            true,
            3000));
      } else if (!model_->GetPlayer()->NotOnlyMainCat()) {
        model_->AddWarning(std::make_shared<Warning>(
            "You don't have enough cats!",
            view_->
                GetCoordinatesForWarning(),
            32,
            true,
            true,
            3000));
      }
    }
  }
}

void Controller::TickWarnings(int delta_time) {
  auto warnings = model_->GetWarnings();
  double shift = 50;
  if (!warnings.empty()) {
    shift += warnings.at(0)->GetFontSize();
    warnings.at(0)->SetShift(static_cast<int>(shift));
    warnings.at(0)->SetIfIsDrawn(true);
  }
  for (size_t i = 1; i < 3 && i < warnings.size(); ++i) {
    shift += warnings.at(i - 1)->GetFontSize();
    shift += 10;
    warnings.at(i)->SetShift(static_cast<int>(shift));
    warnings.at(i)->SetIfIsDrawn(true);
  }
  for (size_t i = 3; i < warnings.size(); ++i) {
    warnings.at(i)->SetIfIsDrawn(false);
  }

  for (auto& warning : warnings) {
    warning->Tick(delta_time);
    warning->SetPosition(view_->GetCoordinatesForWarning());
  }
}

void Controller::CatsAndPortalsIntersect(const std::shared_ptr<Cat>& cat) {
  for (auto& static_object : model_->GetStaticObjects()) {
    if (portal_and_searching_cat_[static_object] == cat) {
      switch (cat->GetCatState()) {
        case CatState::kIsGoingToSearch: {
          model_->SetSelectedPortalSkin(static_object);
          static_object->SetWaitSearchState();
          break;
        }
        case CatState::kIsSearching: {
          model_->SetNormalPortalSkin(static_object);
          static_object->SetSearchState();
          break;
        }
      }
    }
  }
}


