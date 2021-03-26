#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include "GameObject/moving_object.h"
#include "GameObject/cat.h"
#include "player.h"

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void Tick(int time) = 0;
  virtual int GetCurrentTime() = 0;

  virtual Player* GetPlayer() = 0;

  virtual void SetPlayerPosition(const Point& position) = 0;

 private:
  virtual Cat* MakeCat() = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
