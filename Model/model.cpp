#include <algorithm>

#include "../Model/model.h"
#include "../View/progress_bar.h"

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

Model::Model() {
  LoadAnimation();
  for (auto& food : food_) {
    food->SetScaleCoefficientsInRigidBody(0.9, 0.9);
  }
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
  int skin_id = GetRandomSkin();
  static_objects_.back()->SetSkin(objects_pics_["tree"][skin_id]);
  static_objects_.back()->SetSkinId(skin_id);
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
  std::vector<QString> objects_folders = {"food", "tree", "tree_selected"};
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
  std::vector<QString> objects_animations = {"down", "up", "left", "right",};
  for (const auto& animation : objects_animations) {
    std::vector<QPixmap> im{};
    for (int frame_number = 0; frame_number < 4; ++frame_number) {
      QPixmap current =
          QPixmap(path + animation + "/Frame " + QString::number(frame_number) + ".png");
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
          QPixmap(path + animation + "/Frame " + QString::number(frame_number) + ".png");
      im.push_back(current);
    }
    result.emplace_back(im);
  }
  return result;
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

void Model::SetModel() {
  QFontDatabase::addApplicationFont("../resourses/font.ttf");
  std::shared_ptr<Cat> main_cat = std::make_shared<Cat>(Size(40, 40),
                                                        10,
                                                        Point(0, 0));
  main_cat->SetIsInGroup(true);
  QString skin = GetCatRandomSkinPath();
  main_cat->SetAnimations(animations_[skin]);
  cats_.emplace_back(main_cat);

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
