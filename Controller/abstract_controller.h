#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include "../GameObject/food.h"
#include "../GameObject/moving_object.h"
#include "../GameObject/cat.h"
#include "../GameObject/player.h"
#include <list>
#include <memory>
#include "../View/resizer.h"
#include "../View/menu.h"

enum WindowType {
  kMainMenu,
  kGame
};

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void Tick(int time) = 0;
  virtual int GetCurrentTime() = 0;
  virtual void StartGame() = 0;
  virtual WindowType GetWindowType() = 0;
  virtual const Menu& GetMenu() = 0;

  virtual Player* GetPlayer() = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
