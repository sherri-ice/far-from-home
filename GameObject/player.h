#ifndef GAMEOBJECT_PLAYER_H_
#define GAMEOBJECT_PLAYER_H_

#include <list>
#include <memory>
#include <vector>

#include "GameObject/cat.h"
#include "GameObject/dog.h"
#include "GameObject/portal_object.h"
#include "GameObject/view_circle.h"

class Player {
 public:
  Player() = default;
  explicit Player(const std::shared_ptr<Cat>& cat);
  [[nodiscard]] std::vector<std::shared_ptr<Cat>> GetCats() const;

  void OrderCatsToMove(Size velocity);

  void UpdateDogsAround(std::list<std::shared_ptr<Dog>> dogs);
  void UpdateStaticObjectsAround
  (const std::list<std::shared_ptr<PortalObject>>& static_objects);

  void DismissCats();

  [[nodiscard]] const ViewCircle& GetViewCircle() const;
  void SetViewCircle(const ViewCircle& view_circle);
  [[nodiscard]] const Point& GetPosition() const;

  void Tick();

 private:
  std::vector<std::shared_ptr<Cat>> cats_;
  ViewCircle view_circle_;
  Point position_;

  double visibility_radius_{150};
  double group_radius_{20};
};

#endif  // GAMEOBJECT_PLAYER_H_
