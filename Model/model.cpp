#include <algorithm>

#include "../Model/model.h"
#include "../View/progress_bar.h"

Model::Model() {
  LoadAnimation();
  std::shared_ptr<Cat> main_cat = std::make_shared<Cat>(Size(40, 40),
                                                        10,
                                                        Point(0, 0));
  main_cat->SetIsInGroup(true);
  main_cat->SetAnimations(animations_["cat"]);
  cats_.emplace_back(main_cat);
  for (auto& food : food_) {
    food->SetScaleCoefficientsInRigidBody(0.9, 0.9);
  }
  player_ = new Player(main_cat);
  player_->SetViewCircle(ViewCircle(player_->GetPosition(),
                                    constants::kViewCircleDefault));
}

Player* Model::GetPlayer() {
  return player_;
}

std::vector<std::shared_ptr<GameObject>> Model::GetDrawableGameObjects() const {
  std::vector<std::shared_ptr<GameObject>> result;
  for (const auto& cat : cats_) {
    result.push_back(cat);
  }
  for (const auto& dog : dogs_) {
    result.push_back(dog);
  }
  for (const auto& food : food_) {
    result.push_back(food);
  }
  for (const auto& static_object : static_objects_) {
    result.push_back(static_object);
  }
  std::sort(result.begin(), result.end(), [](const
                                             std::shared_ptr<GameObject>& lhs,

                                             const std::shared_ptr<GameObject>&
                                             rhs) {
    return lhs->GetRigidPosition().GetY() < rhs->GetRigidPosition().GetY();
  });
  return result;
}

std::shared_ptr<Cat> Model::MakeNewCat(const Size& size,
                                       double speed,
                                       const Point& point) {
  cats_.push_back(std::make_shared<Cat>(size, speed, point));
  cats_.back()->SetAnimations(animations_["cat"]);
  return cats_.back();
}

void Model::LoadLevel(int level) {
  // TODO(anyone)
}

void Model::SetGameState(int) {
  // TODO(anyone)
}

std::list<std::shared_ptr<Food>> Model::GetFood() {
  return food_;
}

std::list<std::shared_ptr<Dog>> Model::GetDogs() {
  return dogs_;
}

std::list<std::shared_ptr<Cat>> Model::GetCats() {
  return cats_;
}

void Model::ClearObjects() {
  for (auto it = food_.rbegin(); it != food_.rend(); ++it) {
    if ((*it)->IsDead()) {
      food_.remove(*it);
    }
  }

  for (auto it = cats_.rbegin(); it != cats_.rend(); ++it) {
    if ((*it)->IsDead()) {
      cats_.remove(*it);
    }
  }

  for (auto it = dogs_.rbegin(); it != dogs_.rend(); ++it) {
    if ((*it)->IsDead()) {
      dogs_.remove(*it);
    }
  }

  for (auto it = warnings_.rbegin(); it != warnings_.rend(); ++it) {
    if ((*it)->IsDead()) {
      warnings_.remove(*it);
    }
  }
  for (auto it = static_objects_.rbegin(); it != static_objects_.rend();
                                                                        ++it) {
        if ((*it)->IsDead()) {
            static_objects_.remove(*it);
        }
    }
}


std::list<std::shared_ptr<PortalObject>>& Model::GetStaticObjects() {
  return static_objects_;
}

std::shared_ptr<PortalObject> Model::MakeNewPortal(const Size& size,
                                                   const Point& position,
                                                   const QString& skin_path,
                                                   bool has_portal) {
  static_objects_.push_back(std::make_shared<PortalObject>(size,
                                                           position,
                                                           skin_path));
  static_objects_.back()->SetSkin(objects_pics_[1][std::rand() % 3]);
  if (has_portal) {
    static_objects_.back()->SetPortal();
  }
  return static_objects_.back();
}

void Model::AddWarning(const std::shared_ptr<Warning>& warning) {
  warnings_.emplace_back(warning);
}

std::vector<std::shared_ptr<Warning>> Model::GetWarnings() {
  std::vector<std::shared_ptr<Warning>> result;
  for (const auto& warning : warnings_) {
    result.push_back(warning);
  }
  return result;
}

std::shared_ptr<Dog> Model::MakeNewDog(const Size& size,
                                       double speed,
                                       const Point& point,
                                       double visibility_radius,
                                       double walking_speed) {
  dogs_.push_back(std::make_shared<Dog>(size, speed, point, visibility_radius,
                                        walking_speed));
  dogs_.back()->SetAnimations(animations_["dog"]);
  return dogs_.back();
}


std::shared_ptr<Food> Model::MakeNewFood(const Size& size, const Point& point) {
  food_.push_back(std::make_shared<Food>(size, point));
  food_.back()->SetSkin(objects_pics_[0][std::rand() % 3]);
  return food_.back();
}

void Model::LoadAnimation() {
    LoadDinamicAnimation();
    LoadStaticAnimation();
}

void Model::LoadDinamicAnimation() {
    Q_INIT_RESOURCE(images);
  std::vector<QString> paths = {"cat", "dog"};
  for (const auto& path : paths) {
    animations_[path] = GetImagesByFramePath(":images/" + path + "/");
  }
}

void Model::LoadStaticAnimation() {
    Q_INIT_RESOURCE(images);
    QString path_for_objects = ":images/objects/";
    std::vector<QString> objects_folders = {"food", "tree"};
    for (const auto& folder : objects_folders) {
        std::vector<QPixmap> skins;
        for (int i = 0; i < 4; ++i) {
            skins.emplace_back(
                path_for_objects + "/" + folder + "/Frame " + QString::number(i)
                + ".png");
        }
        objects_pics_.emplace_back(skins);
    }
}

std::vector<std::vector<QPixmap>> Model::GetImagesByFramePath(
    const QString& path) const {
  std::vector<std::vector<QPixmap>> result;
  std::vector<QString> objects_animations = {"down", "up", "left", "right"};
  for (const auto& animation : objects_animations) {
    std::vector<QPixmap> im{};
    for (int i = 0; i < 4; ++i) {
      im.emplace_back(
          path + animation + "/Frame " + QString::number(i) + ".png");
    }
    result.emplace_back(im);
  }
  for (int i = 0; i < 4; ++i) {
    std::vector<QPixmap> images{};
    for (int j = 0; j < 4; ++j) {
      images.emplace_back(
          path + "random/" + QString::number(i) + "/Frame " + QString::number(j)
              + ".png");
    }
    result.emplace_back(images);
  }
  return result;
}
