#ifndef GAMEOBJECT_PLAYER_H_
#define GAMEOBJECT_PLAYER_H_

#include "GameObject/cat.h"
#include "view_circle.h"
#include <vector>
#include <memory>

class Player {
 public:
  Player() = default;
  explicit Player(const std::shared_ptr<Cat>& cat);
  [[nodiscard]] std::vector<std::shared_ptr<Cat>> GetCats() const;

  void OrderCatsToMove(Size velocity);

  const ViewCircle& GetViewCircle() const;
  void SetViewCircle(const ViewCircle& view_circle);
  const Point& GetPosition() const;

  void Tick();
 private:
  std::vector<std::shared_ptr<Cat>> cats_;
  ViewCircle view_circle_;
  Point position_;
};

#endif  // GAMEOBJECT_PLAYER_H_
