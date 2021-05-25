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
#include "../Model/music_player.h"

enum WindowType {
  kMainMenu,
  kGame
};

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void Tick(int time) = 0;
  virtual int GetCurrentTime() = 0;
  virtual void ScanIfObjectWereClicked(const Point& point) = 0;
  virtual void StartGame() = 0;
  virtual void EndGame() = 0;

  virtual Player* GetPlayer() = 0;
  virtual std::shared_ptr<MusicPlayer> GetMusicPlayer() = 0;
  virtual void SetGameVolume(int volume) = 0;


  virtual void PauseMusic() = 0;
  virtual void ResumeMusic() = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
