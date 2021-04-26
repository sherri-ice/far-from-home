#include <algorithm>

#include "model.h"

Model::Model() {
    LoadAnimation();
    std::shared_ptr<Cat> main_cat = std::make_shared<Cat>(Size(40, 40),
                                                          0.001, Point());
    cats_.emplace_back(main_cat);


    std::shared_ptr<Dog> dog = std::make_shared<Dog>(Size(40, 40), 7.5,
                                                     Point(250, 250),
                                                     100, 1.75);

    dogs_.emplace_back(dog);


  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(789, 65)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(567, 455)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(210, 270)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(25, 500)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(900, 333)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(300, 100)));
std::cout << "model in begining\n";
  for (auto& food : food_) {
    food->SetScaleCoefficientsInRigidBody(0.9, 0.9);
      std::cout << "model before set skins\n";

      food->SetSkin(objects_pics_[0][std::rand() % 3]);
  }


  player_ = new Player(main_cat);

  // Temporary
  MakeNewCat(Size(60, 60), 0.001, Point(1000, 0));
  MakeNewCat(Size(10, 10), 0.001, Point(500, 500));

  player_->SetViewCircle(ViewCircle(player_->GetPosition(),
                                    constants::kViewCircleDefault));
    for (auto& cat : cats_) {
        cat->SetAnimations(animations_["cat"]);
    }
    for (auto& dog : dogs_) {
        dog->SetAnimations(animations_["dog"]);
    }
    std::cout << "model Set animations\n";


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
  std::sort(result.begin(), result.end(), [](const
                                             std::shared_ptr<GameObject>& lhs,
                                             const std::shared_ptr<GameObject>& rhs) {
    return lhs->GetDrawPosition().GetY() < rhs->GetDrawPosition().GetY();
  });
  return result;
}

std::shared_ptr<Cat> Model::MakeNewCat(const Size& size,
                                       double speed,
                                       const Point& point) {
    Cat new_cat(size, speed, point);
    auto new_cat_ptr = std::make_shared<Cat>(new_cat);
    cats_.push_back(new_cat_ptr);
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
}

void Model::LoadAnimation() {
    std::vector<QString> paths = {"cat", "dog"};
    for (const auto& path : paths) {
        animations_[path] = GetImagesByFramePath("../im/" + path + "/");
    }
    QString path_for_objects = "../im/objects/";
    std::vector<QString> objects_folders = {"food"};
    for (const auto& folder : objects_folders) {
        std::vector<QPixmap> skins;
        for (int i = 0; i < 4; ++i) {
            skins.emplace_back(path_for_objects + "/" + folder + "/Frame " + QString::number(i) + ".png");
        }
        objects_pics_.emplace_back(skins);
    }
}

std::vector<std::vector<QPixmap>> Model::GetImagesByFramePath(const QString &path) const {
//    Q_INIT_RESOURCE(images);
    std::vector<std::vector<QPixmap>> result;
    std::vector<QString> objects_animations = {"down", "up", "left", "right"};
    for (const auto& animation : objects_animations) {
        std::vector<QPixmap> images{};
        for (int i = 0; i < 4; ++i) { // todo change files names
            images.emplace_back(path + animation + "/Frame " + QString::number(i) + ".png");
        }
        result.emplace_back(images);
    }
    for (int i = 0; i < 4; ++i) {
        std::vector<QPixmap> images{};
        for (int j = 0; j < 4; ++j) {
            images.emplace_back(path + "random/" + QString::number(i) + "/Frame " + QString::number(j) + ".png");
        }
        result.emplace_back(images);
    }
    return result;
}
