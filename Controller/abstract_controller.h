#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include "GameObject/cat.h"

enum class GameStatus {
  kWin = 0,
  kLose = 1,
  kPlay = 2
};

enum class Directions {
  kUp,
  kRight,
  kDown,
  kLeft
};

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void StartGame(int level) = 0;
  virtual void EndGame() = 0;
  virtual void Tick(int time) = 0;
  virtual void ClickAction() = 0;
  virtual void GameProcess() = 0;

  virtual MovingObject* GetCat() = 0;

  virtual void GenerateFood() = 0;

  virtual int GetCurrentTime() = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
