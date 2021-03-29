#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include "GameObject/moving_object.h"
#include "GameObject/cat.h"
#include "GameObject/player.h"
#include <memory>

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void Tick(int time) = 0;
  virtual int GetCurrentTime() = 0;
  virtual void StartGame(int level) = 0;

  virtual Player* GetPlayer() = 0;

  virtual void SetPlayerPosition(const Point& position) = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
