#ifndef GAMEOBJECT_PLAYER_H_
#define GAMEOBJECT_PLAYER_H_

#include <list>
#include <memory>
#include <vector>
#include <set>

#include "../Model/timer.h"
#include "../Model/group.h"
#include "../GameObject/cat.h"
#include "../GameObject/dog.h"
#include "view_circle.h"
#include "portal_object.h"

namespace constants {
const double kChangeSpeedCoefficient = 1.2;
}

enum class HungerState {
  kNotHungry,
  kMediumHunger,
  kSevereHunger
};

class Player {
 public:
  Player() = default;
  explicit Player(const std::shared_ptr<Cat>& cat);
  [[nodiscard]] std::vector<std::shared_ptr<Cat>> GetCats() const;

  void OrderCatsToMove(Size velocity_from_player);
  Point GenerateRandomDestination() const;

  void UpdateDogsAround(const std::vector<std::shared_ptr<Dog>>& dogs) const;

  void UpdateStaticObjectsAround
      (const std::vector<std::shared_ptr<PortalObject>>& static_objects);

  void IsReachable(const std::vector<std::shared_ptr<Dog>>& dogs);
  void UpdateCatsGroup(const std::vector<std::shared_ptr<Cat>>& all_cats);

  void DismissCats();
  void GroupTick(int time);

  [[nodiscard]] const ViewCircle& GetViewCircle() const;
  [[nodiscard]] const Group& GetCatGroup() const;
  std::shared_ptr<Cat> GetMainCat();
  void SetViewCircle(const ViewCircle& view_circle);
  [[nodiscard]] const Point& GetPosition() const;

  void LosingCat(Point dog_position, const std::shared_ptr<Cat>& cat);
  std::shared_ptr<Cat> SendCatToSearch(const Point& portal_coordinates, int
  search_time, const Rect& portal_rect);
    void SendCatToPortal(const std::shared_ptr<Cat>& cat);

  void Tick();
  bool NotOnlyMainCat();

  void FeedCats(double food);
  void UpdateHunger();
  void DecHunger(double hunger);
  double GetFoodSaturation() const;
  int GetMaxFoodSaturation() const;

  bool IfNeedToShowFirstWarning() const;
  bool IfNeedToShowSecondWarning() const;
  void ResetNeedToShowWarnings();

 private:
  std::vector<std::shared_ptr<Cat>> cats_;
  ViewCircle view_circle_ = ViewCircle();
  Group cat_group_;
  std::vector<std::shared_ptr<Cat>> free_cats_;

  double visibility_radius_{200};

  double food_saturation_;
  double speed_of_hunger_;
  int max_food_saturation_{100};
  HungerState hunger_state_{HungerState::kNotHungry};

  bool need_to_show_first_warning_{false};
  bool need_to_show_second_warning_{false};

  static std::mt19937 random_generator_;
};

#endif  // GAMEOBJECT_PLAYER_H_
