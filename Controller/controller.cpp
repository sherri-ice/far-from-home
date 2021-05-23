#include "controller.h"

Controller::Controller() {
  model_ = std::make_shared<Model>();
  view_ = std::make_shared<View>(this, model_);
  map_generator_.SetModel(model_);
  map_generator_.GenerateMap();
}

void Controller::Tick(int time) {
  int delta_time = time - current_game_time_;
  current_game_time_ = time;

  TickPlayer(delta_time);
  CheckIfDestinationIsInsideStaticObject();
  CheckIfDestinationIntersectsWithCat();

  TickFood(delta_time);
  TickHunger();

  TickCats(delta_time);
  TickDogs(delta_time);
  MoveCatsAndDogs(delta_time);
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
  model_->SetGameState(GameState::kGame);
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
      cat->Tick(delta_time);
      MovingAndStaticObjectsIntersect(cat);
      CatsAndPortalsIntersect(cat);
      if (cat->GetIsInGroup() && !cat->IsMainCat()) {
        CatsInGroupIntersect(cat);
      } else if (cat->IsMainCat()) {
        MainCatIntersectsWithCats(cat);
      } else {
        WildCatsAndDogsIntersect(cat);
      }
      cat->TickAnimation(delta_time);
    }
  }
}

void Controller::TickDogs(int delta_time) {
  std::list<std::shared_ptr<Dog>> dogs = model_->GetDogs();
  auto player = model_->GetPlayer();
  for (auto& dog : dogs) {
    if (view_->IsOnTheScreen(dog)) {
      dog->SetReachableCat(player->GetCats());
      dog->Tick(delta_time);
      MovingAndStaticObjectsIntersect(dog);
      DogsIntersect(dog);
      dog->TickAnimation(delta_time);
      for (auto& cat : player->GetCats()) {
        if (dog->GetRigidBody()->IsCollide(*(cat->GetRigidBody()))) {
          if (cat == player->GetMainCat()) {
            player->DismissCats();
            dog->SetIsMainCatCaught(true);
            break;
          } else {
            if (!cat->GetIsBusy()) {
              player->LosingCat(dog->GetRigidPosition(), cat);
            }
          }
        }
      }
    }
  }
}

void Controller::TickFood(int time) {
  for (auto& food : model_->GetFood()) {
    food->Tick(time);
  }
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
  auto player = model_->GetPlayer();
  for (const auto& player_cat : player->GetCats()) {
    for (auto& food : model_->GetFood()) {
      if (player_cat->GetRigidBody()->IsCollide(*(food->GetRigidBody()))) {
        player->FeedCats(food->GetFoodQuality());
        food->SetIsDead();
      }
    }
  }
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
          ->GetVelocityToGoAround(*(static_object->GetRigidBody()),
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
        // todo pause
        if (view_->GetResultWindow().GetUserAnswer()) {
          // loose cat
        }
        object->SetCollectedState();
        continue;
      }
      if (!object->IsCollected()
          && model_->GetPlayer()->NotOnlyMainCat()) {
            auto cat = model_->GetPlayer()->SendCatToSearch
                (object->GetRigidPosition(), object->GetSearchTime(), object
                ->GetRigidBody()->GetRect());
        portal_and_searching_cat_[object] = cat;
      }
      if (object->IsCollected()) {
        model_->AddWarning(std::make_shared<Warning>(
            "You've already searched a portal here!",
            view_->
                GetCoordinatesForWarning(),
            32,
            true,
            true,
            3000));
      }
      if (!model_->GetPlayer()->NotOnlyMainCat()) {
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
        case CatState::kHasFinishedSearching: {
          portal_and_searching_cat_.erase(static_object);
          break;
        }
      }
    }
  }
}

void Controller::TickHunger() {
  auto player = model_->GetPlayer();
  player->UpdateHunger();
  model_->GetProgressBar()->SetMaxValue(player->GetMaxFoodSaturation());
  model_->GetProgressBar()->UpdateCurrentValue(static_cast<int>
    (player->GetFoodSaturation()));
  if (player->IfNeedToShowFirstWarning()) {
    model_->AddWarning(std::make_shared<Warning>("Your cat is hungry!",
                                                 view_->
                                                 GetCoordinatesForWarning(),
                                                 32,
                                                 true,
                                                 true,
                                                 3000));
    player->ResetNeedToShowWarnings();
    model_->GenerateFood(player->GetPosition(), view_->GetWidthOfScreenAsGame(),
                         view_->GetHeightOfScreeAsGame(), 10);
  }
  if (player->IfNeedToShowSecondWarning()) {
    model_->AddWarning(std::make_shared<Warning>("Your cat is extremely "
                                                 "hungry!!! Go on and feed "
                                                 "him!!!",
                                                 view_->
                                                 GetCoordinatesForWarning(),
                                                 32,
                                                 true,
                                                 true,
                                                 3500));
    player->ResetNeedToShowWarnings();
    model_->GenerateFood(player->GetPosition(), view_->GetWidthOfScreenAsGame(),
                         view_->GetHeightOfScreeAsGame(), 15);
  }
}

void Controller::CheckIfDestinationIsInsideStaticObject() {
  auto player = model_->GetPlayer();
  auto player_cats = player->GetCats();
  auto static_objects = model_->GetStaticObjects();
  for (int i{0}; i < player_cats.size(); ++i) {
    if (player_cats.at(i)->IsComingDestination()) {
      auto destination = player_cats.at(i)->GetDestination();
      for (const auto& static_object : static_objects) {
        if (view_->IsOnTheScreen(static_object)) {
          while (static_object->GetRigidBody()->IsDestinationCollideWithRect
          (player_cats.at(i)->GetRigidBody()->GetRectInNewPosition
          (destination))) {
            destination = player->GenerateRandomDestination();
          }
          player_cats.at(i)->SetDestination(destination);
        }
      }
    }
  }
}

void Controller::DogsIntersect(const std::shared_ptr<Dog>& dog) {
  auto rigid_body = dog->GetRigidBody();
  for (const auto& other_dog : model_->GetDogs()) {
    if (view_->IsOnTheScreen(other_dog) && other_dog != dog) {
      auto current_velocity = dog->GetVelocity();
      if (rigid_body->IfCollisionWillHappen(*(other_dog->GetRigidBody()),
                                            current_velocity)) {
        Size new_velocity = rigid_body->GetVelocityToGoAround(*
            (other_dog->GetRigidBody()), current_velocity, other_dog->GetVelocity());
        dog->SetVelocity(new_velocity * current_velocity.GetLength());
      }
    }
  }
  for (const auto& cat : model_->GetCats()) {
    auto current_velocity = dog->GetVelocity();
    if (view_->IsOnTheScreen(cat) && !cat->GetIsInGroup() &&
    rigid_body->IfCollisionWillHappen(*(cat->GetRigidBody()),
                                      current_velocity)) {
      auto new_velocity = rigid_body->GetVelocityToGoAround(*
          (cat->GetRigidBody()), current_velocity, cat->GetVelocity());
      dog->SetVelocity(new_velocity * current_velocity.GetLength());
    }
  }
}

void Controller::CatsInGroupIntersect(const std::shared_ptr<Cat>& cat) {
  auto rigid_body = cat->GetRigidBody();
  auto main_cat = model_->GetPlayer()->GetMainCat();
  if (rigid_body->IfCollisionWillHappen(*(main_cat->GetRigidBody()),
                                        cat->GetVelocity()) &&
                                        main_cat->GetVelocity() !=
                                        cat->GetVelocity()) {
    auto new_velocity = rigid_body->GetVelocityToGoAround(*
        (main_cat->GetRigidBody()), cat->GetVelocity(), main_cat->GetVelocity
        ());
    cat->SetVelocity(new_velocity * cat->GetVelocity().GetLength());
  }
  auto cats = model_->GetPlayer()->GetCats();
  for (int i{1}; i < cats.size(); ++i) {
    auto current_velocity = cat->GetVelocity();
    if (cat != cats.at(i) && rigid_body->IfCollisionWillHappen(*(cats.at(i)
    ->GetRigidBody()), current_velocity)) {
      auto new_velocity = rigid_body->GetVelocityToGoAround(*(cats.at(i)
          ->GetRigidBody()), current_velocity, cats.at(i)->GetVelocity());
      cat->SetVelocity(new_velocity * current_velocity.GetLength());
    }
  }
}

void Controller::CheckIfDestinationIntersectsWithCat() {
  auto player = model_->GetPlayer();
  auto player_cats = player->GetCats();
  for (int i{1}; i < player_cats.size(); ++i) {
    if (player_cats.at(i)->IsComingDestination()) {
      auto destination = player_cats.at(i)->GetDestination();
      for (const auto& cat : player_cats) {
        if (cat != player_cats.at(i)) {
          while (cat->GetRigidBody()->IsDestinationCollideWithRect
          (player_cats.at(i)->GetRigidBody()->GetRectInNewPosition
          (destination))) {
            destination = player->GenerateRandomDestination();
          }
          player_cats.at(i)->SetDestination(destination);
        }
      }
    }
  }
}

void Controller::WildCatsAndDogsIntersect(const std::shared_ptr<Cat>& cat) {
  auto rigid_body = cat->GetRigidBody();
  for (const auto& dog : model_->GetDogs()) {
    auto current_velocity = cat->GetVelocity();
    auto other_rect = dog->GetRigidBody()->GetRect();
    if (view_->IsOnTheScreen(dog) && rigid_body->IfCollisionWillHappen(*(dog
    ->GetRigidBody()), current_velocity)) {
      auto new_velocity = rigid_body->GetVelocityToGoAround(*
          (dog->GetRigidBody()), current_velocity, dog->GetVelocity());
      cat->SetVelocity(new_velocity * current_velocity.GetLength());
    }
  }
  for (const auto& other_cat : model_->GetCats()) {
    auto current_velocity = cat->GetVelocity();
    if (view_->IsOnTheScreen(other_cat)  && other_cat != cat &&
    rigid_body->IfCollisionWillHappen(*(other_cat->GetRigidBody()),
                                      current_velocity)) {
      auto new_velocity = rigid_body->GetVelocityToGoAround(*
          (other_cat->GetRigidBody()), current_velocity,
          other_cat->GetVelocity());
      cat->SetVelocity(new_velocity * current_velocity.GetLength());
    }
  }
}

void Controller::MainCatIntersectsWithCats(const std::shared_ptr<Cat>& main_cat) {
  auto rigid_body = main_cat->GetRigidBody();
  auto cats = model_->GetCats();
  for (auto& cat : cats) {
    if (main_cat != cat && view_->IsOnTheScreen(cat) &&
    rigid_body->IfCollisionWillHappen(*(cat->GetRigidBody()), main_cat->GetVelocity())) {
      auto current_velocity = cat->GetVelocity();
      auto new_velocity = rigid_body->GetVelocityToGoAround(*
          (cat->GetRigidBody()), main_cat->GetVelocity(), current_velocity);
      if (cat->GetIsInGroup()) {
        cat->SetVelocity(main_cat->GetVelocity());
      } else {
        main_cat->SetVelocity(new_velocity * main_cat->GetVelocity()
        .GetLength());
      }
    }
  }
}

void Controller::MoveCatsAndDogs(int delta_time) {
  for (auto& cat : model_->GetCats()) {
    if (view_->IsOnTheScreen(cat)) {
      cat->Move(delta_time);
    }
  }
  for (auto& dog : model_->GetDogs()) {
    if (view_->IsOnTheScreen(dog)) {
      dog->Move(delta_time);
    }
  }
}
