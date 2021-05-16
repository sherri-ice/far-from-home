#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include "../GameObject/food.h"
#include "../GameObject/moving_object.h"
#include "../GameObject/cat.h"
#include "../GameObject/player.h"
#include <list>
#include <memory>
#include "../View/resizer.h"

enum class WindowType {
  kMainMenu = 1,
  kSettings = 2,
  kPauseMenu = 3,
  kGame = 0,
};

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void SecondConstructorPart() = 0;

  virtual QPixmap GetBackground(WindowType type) const = 0;


  virtual void Tick(int time) = 0;
  virtual int GetCurrentTime() = 0;
  virtual void StartGame() = 0;
  virtual void EndGame() = 0;

  virtual Player* GetPlayer() = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
