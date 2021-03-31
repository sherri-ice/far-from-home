#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <GameObject/food.h>
#include "GameObject/moving_object.h"
#include "GameObject/cat.h"
#include "GameObject/player.h"
#include<list>
#include <memory>

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void Tick(int time) = 0;
  virtual int GetCurrentTime() = 0;
  virtual void StartGame(int level) = 0;

  virtual std::shared_ptr<Player> GetPlayer() = 0;

  virtual void SetPlayerPosition(const Point& position) = 0;
  virtual const std::list<std::shared_ptr<Food>>& GetFood() const = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
