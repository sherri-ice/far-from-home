#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <list>
#include <memory>

#include "../Controller/abstract_controller.h"
#include "../Model/model.h"
#include "../View/view.h"

#include "../Model/generator.h"

class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void StartGame() override;
  void EndGame() override;
  void Tick(int time) override;
  int GetCurrentTime() override;

  Player* GetPlayer() override;
  void SetGameVolume(int volume) override;
  std::shared_ptr<MusicPlayer> GetMusicPlayer() override;

  void PauseMusic() override;
  void ResumeMusic() override;

 private:
  void TickPlayer(int delta_time);
  void TickCats(int time);
  void TickDogs(int delta_time);
  void TickFood(int time);
  void TickViewCircle();

  void CatsAndFoodIntersect();

  int current_game_time_{0};
  std::shared_ptr<Model> model_;
  std::shared_ptr<View> view_;
  Generator map_generator_;
  std::shared_ptr<MusicPlayer> music_player_;
};

#endif  // CONTROLLER_CONTROLLER_H_
