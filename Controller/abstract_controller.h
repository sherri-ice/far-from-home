#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include "GameObject/food.h"
#include "GameObject/moving_object.h"
#include "GameObject/cat.h"
#include "GameObject/player.h"
#include<list>
#include <memory>
#include <View/resizer.h>

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void Tick(int time) = 0;
  virtual int GetCurrentTime() = 0;
  virtual void StartGame(int level) = 0;

  virtual void TickPlayer() = 0;

  virtual void CatsAndFoodIntersect() = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
