#include <algorithm>

#include "../Model/model.h"

namespace {

int GetRandomSkin() {
  std::mt19937 random_generator = std::mt19937
      (std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int>
      random_id_generator(0, 3);
  return random_id_generator(random_generator);
}
}  // namespace

std::mt19937 Model::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());

Model::Model() : hunger_bar_(100, 100) {
  LoadAnimation();
  QFontDatabase::addApplicationFont("../resourses/font.ttf");
  for (auto& food : food_) {
    food->SetScaleCoefficientsInRigidBody(0.9, 0.9);
  }
  hunger_bar_.SetSkin(objects_pics_["progress_bar"][0]);
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
  QString skin = GetCatRandomSkinPath();
  cats_.back()->SetAnimations(animations_[skin]);
  return cats_.back();
}

void Model::LoadLevel(int level) {
}

void Model::SetGameState(int) {
}

std::vector<std::shared_ptr<Food>> Model::GetFood() {
  return food_;
}

std::vector<std::shared_ptr<Dog>> Model::GetDogs() {
  return dogs_;
}

std::vector<std::shared_ptr<Cat>> Model::GetCats() {
  return cats_;
}

void Model::ClearObjects() {
  for (int i = food_.size() - 1; i >= 0; --i) {
    if (food_.at(i)->IsDead()) {
      food_.erase(food_.begin() + i);
    }
  }

  for (int i = cats_.size() - 1; i >= 0; --i) {
    if (cats_.at(i)->IsDead()) {
      cats_.erase(cats_.begin() + i);
    }
  }

  for (int i = dogs_.size() - 1; i >= 0; --i) {
    if (dogs_.at(i)->IsDead()) {
      dogs_.erase(dogs_.begin() + i);
    }
  }

  for (int i = warnings_.size() - 1; i >= 0; --i) {
    if (warnings_.at(i)->IsDead()) {
      warnings_.erase(warnings_.begin() + i);
    }
  }
  for (int i = static_objects_.size() - 1; i >= 0; --i) {
    if (static_objects_.at(i)->IsDead()) {
      static_objects_.erase(static_objects_.begin() + i);
    }
  }
}

std::vector<std::shared_ptr<PortalObject>>& Model::GetStaticObjects() {
  return static_objects_;
}

std::shared_ptr<PortalObject> Model::MakeNewPortal(const Size& size,
                                                   const Point& position,
                                                   bool has_portal) {
  static_objects_.push_back(std::make_shared<PortalObject>(size,
                                                           position));
  int skin_id = GetRandomSkin();
  static_objects_.back()->SetSkin(objects_pics_["tree"][skin_id]);
  static_objects_.back()->SetSkinId(skin_id);
  if (skin_id == 2) {
    static_objects_.back()->SetScaleCoefficientsInRigidBody(0.34, 0.3);
  } else {
    static_objects_.back()->SetScaleCoefficientsInRigidBody(0.3, 0.3);
  }
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
  QString skin = GetDogRandomSkinPath();
  dogs_.back()->SetAnimations(animations_[skin]);
  return dogs_.back();
}

std::shared_ptr<Food> Model::MakeNewFood(const Size& size, const Point& point) {
  food_.push_back(std::make_shared<Food>(size, point));
  int skin_id = GetRandomSkin();
  food_.back()->SetSkin(objects_pics_["food"][skin_id]);
  food_.back()->SetSkinId(skin_id);
  return food_.back();
}

void Model::LoadStaticAnimation() {
  Q_INIT_RESOURCE(images);
  QString path_for_objects = ":images/objects/";
  std::vector<QString> objects_folders = {"food", "tree", "tree_selected",
                                          "progress_bar"};
  for (const auto& folder : objects_folders) {
    std::vector<QPixmap> skins;
    for (int i = 0; i < 4; ++i) {
      skins.emplace_back(
          path_for_objects + "/" + folder + "/Frame " + QString::number(i)
              + ".png");
    }
    objects_pics_[folder] = skins;
  }
}

std::vector<std::vector<QPixmap>> Model::GetImagesByFramePath(
    const QString& path) const {
  std::vector<std::vector<QPixmap>> result;
  std::vector<QString> objects_animations = {"down", "up", "left", "right"};
  for (const auto& animation : objects_animations) {
    std::vector<QPixmap> im{};
    for (int frame_number = 0; frame_number < 4; ++frame_number) {
      QPixmap current =
          QPixmap(path + animation + "/Frame " + QString::number
          (frame_number) + ".png");
      im.push_back(current);
    }
    result.emplace_back(im);
  }
  for (int i = 0; i < 2; ++i) {
    std::vector<QPixmap> images{};
    for (int j = 0; j < 4; ++j) {
      images.emplace_back(
          path + "random/" + QString::number(i) + "/Frame " + QString::number(j)
              + ".png");
    }
    result.emplace_back(images);
  }
  objects_animations = {"send home", "dead cat"};
  for (const auto& animation : objects_animations) {
    std::vector<QPixmap> im{};
    for (int frame_number = 0; frame_number < 4; ++frame_number) {
      QPixmap current =
          QPixmap(path + animation + "/Frame " + QString::number
          (frame_number) + ".png");
      im.push_back(current);
    }
    result.emplace_back(im);
  }
  return result;
}

void Model::LoadAnimation() {
  Q_INIT_RESOURCE(images);
  std::vector<QString> paths;
  for (int i{0}; i < 8; ++i) {
    QString path = "../images/cats skins/" + QString::number(i) + "/";
    paths.push_back(path);
  }
  for (int i{0}; i < 5; ++i) {
    QString path = "../images/dogs skins/" + QString::number(i) + "/";
    paths.push_back(path);
  }
  for (const auto& path : paths) {
    animations_[path] = GetImagesByFramePath(path);
  }
  LoadStaticAnimation();
}

void Model::SetSelectedPortalSkin(std::shared_ptr<PortalObject> portal) {
  auto id = portal->GetSkinId();
  auto new_skin = objects_pics_["tree_selected"].at(id);
  portal->SetSkin(new_skin);
}

void Model::SetNormalPortalSkin(std::shared_ptr<PortalObject> portal) {
  auto id = portal->GetSkinId();
  auto new_skin = objects_pics_["tree"].at(id);
  portal->SetSkin(new_skin);
}

void Model::SetModel() {
  MakeNewCat(Size(50, 50), 10, Point());
  auto main_cat = cats_.back();
  main_cat->SetIsInGroup(true);
  QString skin = GetCatRandomSkinPath();
  main_cat->SetAnimations(animations_[skin]);
  player_ = new Player(main_cat);
  player_->SetViewCircle(ViewCircle(player_->GetPosition(),
                                    constants::kViewCircleDefault));
}

void Model::ClearModel() {
  cats_.clear();
  food_.clear();
  dogs_.clear();
  static_objects_.clear();
}

void Model::ChangeLanguage(Language lang) {
}

void Model::GenerateFood(const Point& player_position, double
  window_width, double window_height, int number_of_food) {
  double part_of_height = 0.5 * window_height;
  double part_of_width = 0.5 * window_width;
  double width = part_of_width + constants::kWidthForFoodGeneration;
  double height = part_of_height + constants::kHeightForFoodGeneration;
  std::uniform_int_distribution<> top_and_bottom_x(
      static_cast<int>(player_position.GetX() - width),
      static_cast<int>(player_position.GetX() + width));
  std::uniform_int_distribution<> left_area_x(
      static_cast<int>(player_position.GetX() - width),
      static_cast<int>(player_position.GetX() - part_of_width));
  std::uniform_int_distribution<> right_area_x(
      static_cast<int>(player_position.GetX() + part_of_width),
      static_cast<int>(player_position.GetX() + width));

  std::uniform_int_distribution<> top_area_y(
      static_cast<int>(player_position.GetY() - height),
      static_cast<int>(player_position.GetY() - part_of_height));
  std::uniform_int_distribution<> bottom_area_y(
      static_cast<int>(player_position.GetY() + part_of_height),
      static_cast<int>(player_position.GetY() + height));
  std::uniform_int_distribution<> same_height_area(
      static_cast<int>(player_position.GetY() - part_of_height),
      static_cast<int>(player_position.GetY() + part_of_height));

  int num_of_food_for_large_areas = number_of_food / 3;
  int num_of_food_for_small_areas = (number_of_food -
      num_of_food_for_large_areas * 2) / 2;

  for (int i = 0; i < num_of_food_for_large_areas; ++i) {
    MakeNewFood(Size(20, 20), Point(top_and_bottom_x(random_generator_),
                                    top_area_y(random_generator_)));
    MakeNewFood(Size(20, 20), Point(top_and_bottom_x(random_generator_),
                                    bottom_area_y(random_generator_)));
  }
  for (int i = 0; i < num_of_food_for_small_areas; ++i) {
    MakeNewFood(Size(20, 20), Point(left_area_x(random_generator_),
                                    same_height_area(random_generator_)));
    MakeNewFood(Size(20, 20), Point(right_area_x(random_generator_),
                                    same_height_area(random_generator_)));
  }
}

GlobalProgressBar* Model::GetProgressBar() {
  return &hunger_bar_;
}

QString Model::GetCatRandomSkinPath() {
  std::uniform_int_distribution<> random_time(0, 7);
  QString path = "../images/cats skins/" + QString::number(random_time
      (random_generator_)) + "/";
  return path;
}

QString Model::GetDogRandomSkinPath() {
  std::uniform_int_distribution<> random_time(0, 4);
  QString path = "../images/dogs skins/" + QString::number(random_time
      (random_generator_)) + "/";
  return path;
}
