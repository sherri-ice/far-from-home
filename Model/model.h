#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <list>
#include <memory>
#include <vector>
#include <map>

#include "../GameObject/cat.h"
#include "../GameObject/dog.h"
#include "../GameObject/food.h"
#include "../GameObject/player.h"
#include "../View/global_progress_bar.h"
#include "../View/resizer.h"

enum Language {
  kRussian,
  kEnglish
};

class Model {
 public:
  Model();
  void LoadLevel(int level);
  void SetModel();

  Player* GetPlayer();
  [[nodiscard]] std::vector<std::shared_ptr<GameObject>>
  GetDrawableGameObjects() const;
  void SetGameState(int game_state);
  std::shared_ptr<Cat> MakeNewCat(const Size& size,
                                  double speed,
                                  const Point& point);

  std::shared_ptr<PortalObject> MakeNewPortal(const Size& size,
                                              const Point& position,
                                              const QString& skin_path,
                                              bool has_portal);
  void AddWarning(const std::shared_ptr<Warning>& warning);

  std::shared_ptr<Dog> MakeNewDog(const Size& size,
                                  double speed,
                                  const Point& point,
                                  double visibility_radius,
                                  double waking_speed);
  std::shared_ptr<Food> MakeNewFood(const Size& size, const Point& point);


  std::list<std::shared_ptr<Food>> GetFood();
  std::list<std::shared_ptr<Dog>> GetDogs();
  std::list<std::shared_ptr<Cat>> GetCats();

  std::list<std::shared_ptr<PortalObject>>& GetStaticObjects();
  std::vector<std::shared_ptr<Warning>> GetWarnings();

  void ClearObjects();
  void ClearModel();

  void LoadDynamicAnimation();
  void LoadStaticAnimation();
  void LoadAnimation();

  void ChangeLanguage(Language lang);

  [[nodiscard]] std::vector<std::vector<QPixmap>> GetImagesByFramePath
      (const QString& path) const;

  void SetSelectedPortalSkin(std::shared_ptr<PortalObject> portal);
  void SetNormalPortalSkin(std::shared_ptr<PortalObject> portal);

  void SetCatHidingAnimation(std::shared_ptr<Cat> cat);
  void SetCatGettingOutAnimation(std::shared_ptr<Cat> cat);

  void GenerateFood(const Point& player_position, double width,
                    double height, int number_of_food);

  GlobalProgressBar* GetProgressBar();

 private:
  std::map<QString, std::vector<std::vector<QPixmap>>> animations_;
  std::map<QString, std::vector<QPixmap>> objects_pics_{};
  int current_level_ = 0;

  std::list<std::shared_ptr<Cat>> cats_;
  Player* player_;
  std::list<std::shared_ptr<Food>> food_;
  std::list<std::shared_ptr<Dog>> dogs_;
  Language lang_ = Language::kEnglish;
  std::list<std::shared_ptr<PortalObject>> static_objects_;
  std::list<std::shared_ptr<Warning>> warnings_;

  GlobalProgressBar hunger_bar_;

  static std::mt19937 random_generator_;
};

#endif  // MODEL_MODEL_H_
