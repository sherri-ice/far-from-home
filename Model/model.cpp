#include <algorithm>

#include "model.h"

Model::Model() {
    std::vector<int> path;
    std::vector<QString> time;
    LoadAnimation(path, time);

    std::shared_ptr<Cat> main_cat = std::make_shared<Cat>(Size(50, 60),
                                                            0.001, Point());

  //------------------
  main_cat->SetAnimations(animations_["cat"]);



  cats_.emplace_back(main_cat);

  std::shared_ptr<Dog> dog = std::make_shared<Dog>(Size(80, 60), 0.00075,
                                                   Point(250, 250), 100);
  dogs_.emplace_back(dog);

  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(789, 65)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(567, 455)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(210, 270)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(25, 500)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(900, 333)));
  food_.emplace_back(std::make_shared<Food>(Size(20, 20), Point(300, 100)));

  for (auto &food : food_) {
    food->SetScaleCoefficientsInRigidBody(0.9, 0.9);
  }

  player_ = new Player(main_cat);

  // Temporary
    std::cout << "model constructor\n";
    MakeNewCat(Size(50, 60), 0.001, Point(1000, 0));
    MakeNewCat(Size(50, 60), 0.001, Point(500, 500));

    player_->SetViewCircle(ViewCircle(player_->GetPosition(),
                                    constants::kViewCircleDefault));

}

Player* Model::GetPlayer() {
  return player_;
}

std::vector<std::shared_ptr<GameObject>> Model::GetDrawableGameObjects() const {
  std::vector<std::shared_ptr<GameObject>> result;
    std::cout << "getdrawableobject1\n";

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
  std::shared_ptr<GameObject>& lhs, const std::shared_ptr<GameObject>& rhs) {
    return lhs->GetDrawPosition().GetY() < rhs->GetDrawPosition().GetY();
  });
  std::cout << "getdrawableobject\n";
  return result;
}

std::shared_ptr<Cat> Model::MakeNewCat(const Size& size,
                                       double speed,
                                       const Point& point) {
  Cat new_cat(size, speed, point);
    new_cat.SetAnimations(animations_["cat"]);
    auto new_cat_ptr = std::make_shared<Cat>(new_cat);
    std::cout << "new cat setting anim before\n";

    cats_.push_back(new_cat_ptr);
    std::cout << "new cat setting anim after\n";

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

void Model::LoadAnimation(const std::vector<int> &timings,
                          const std::vector<QString> &paths) { // todo i dont know what im doing
    //  todo  somehow fill map with animations

    //-----------------

    std::vector<std::vector<QPixmap>> temp;
    temp.resize(7);
    temp = GetImagesByFramePath();
    animations_["cat"] = temp;
    //-----------------

//    std::vector<AnimationPlayer> animations;
//    animations.reserve(timings.size());
//    for (uint32_t i = 0; i < timings.size(); i++) {
//        animations.emplace_back(GetImagesByFramePath(paths[i]), timings[i]);
//    }
//    object->SetAnimationPlayers(std::move(animations));
}

std::vector<std::vector<QPixmap>> Model::GetImagesByFramePath(
        const QString& animation_last_frames, const QString& picture_type) const { // todo
//    QString clear_path = "../im/Group " + animation_last_frames;
//    QStringList splitted_path = clear_path.split("_");
//
    auto images = std::vector<std::vector<QPixmap>>();
    images.resize(7);

//    int count = splitted_path.back().toInt();

//    for (int j = 0; j < 9; ++j) {
    for (int j = 5; j < 7; ++j) {
        std::vector<QPixmap> animation{};
        for (int i = 1; i <= 27; i++) {
//        splitted_path.back() = QString::number(i);
//        images.emplace_back(clear_path + QString(i) + ".png");
            QString path ="../im/Frame" + QString::number(j - 4) + " " + QString::number(i) + ".png";
            animation.emplace_back(path);
        }
        images[j] = animation;
    }
    return images;
}

