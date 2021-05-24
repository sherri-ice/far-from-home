#include <algorithm>

#include "model.h"

Model::Model() {
  LoadAnimation();
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
  std::shared_ptr<GameObject>& lhs, const std::shared_ptr<GameObject>& rhs) {
    return lhs->GetDrawPosition().GetY() < rhs->GetDrawPosition().GetY();
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
    for (auto it = static_objects_.rbegin(); it != static_objects_.rend();
                                                                        ++it) {
        if ((*it)->IsDead()) {
            static_objects_.remove(*it);
        }
    }
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

std::shared_ptr<GameObject> Model::MakeNewStaticObject(const Size& size,
                                                       const Point& point) {
  static_objects_.push_back(std::make_shared<GameObject>(size, point));
  static_objects_.back()->SetSkin(objects_pics_[1][std::rand() % 3]);
  return static_objects_.back();
}

const std::list<std::shared_ptr<GameObject>>& Model::GetStaticObjects() const {
  return static_objects_;
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

void Model::SetModel() {
  MakeNewCat(Size(50, 50), 10, Point());
  auto main_cat = cats_.back();
  main_cat->SetIsInGroup(true);
  main_cat->SetAnimations(animations_["cat"]);
  player_ = new Player(main_cat);
  player_->SetViewCircle(ViewCircle(player_->GetPosition(),
                                    constants::kViewCircleDefault));
}
// QPixmap Model::GetBackground(int type) const {
//   return type < 2 ? backgrounds_[type] : backgrounds_[2];
// }
void Model::ClearModel() {
  cats_.erase(cats_.begin(), cats_.end());
  food_.erase(food_.begin(), food_.end());
  dogs_.erase(dogs_.begin(), dogs_.end());
  static_objects_.erase(static_objects_.begin(), static_objects_.end());
  player_->Clear();
}
