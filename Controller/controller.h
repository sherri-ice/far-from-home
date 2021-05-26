#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <vector>
#include <map>
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
  void TickWin();

  Player* GetPlayer() override;
  void SetGameVolume(int volume) override;
  std::shared_ptr<MusicPlayer> GetMusicPlayer() override;

  void PauseMusic() override;
  void ResumeMusic() override;

  void ScanIfObjectWereClicked(const Point& point) override;

 private:
  void TickPlayer(int delta_time);
  void TickCats(int time);
  void TickDogs(int delta_time);
  void TickFood(int delta_time);
  void TickObjects(int delta_time);
  void TickWarnings(int delta_time);
  void TickViewCircle();
  void TickHunger();
  void MoveCatsAndDogs(int delta_time);
  void TickWin();
  void CatsAndFoodIntersect();
  void CatAndStaticObjectsIntersect(const std::shared_ptr<Cat>& cat);
  void DogAndStaticObjectIntersect(const std::shared_ptr<Dog>& dog);
  void CatsAndPortalsIntersect(const std::shared_ptr<Cat>& cat);
  void CatAndDogInteraction();

  void CheckIfDestinationIsInsideStaticObject();
  void CheckIfDestinationIntersectsWithCat();

  void DogsIntersect(const std::shared_ptr<Dog>& dog);
  void CatsInGroupIntersect(const std::shared_ptr<Cat>& cat);
  void WildCatsAndOtherCatsIntersect(const std::shared_ptr<Cat>& cat);
  void MainCatIntersectsWithCats(const std::shared_ptr<Cat>& main_cat);
  void CatsAndDogIntersect(const std::shared_ptr<Cat>& cat);
  void MovingAndStaticObjectsIntersect(const std::shared_ptr<MovingObject>&
  moving_object);

  int current_game_time_{0};
  std::shared_ptr<Model> model_;
  std::shared_ptr<View> view_;
  Generator map_generator_;
  std::map<std::shared_ptr<PortalObject>, std::shared_ptr<Cat>>
      portal_and_searching_cat_;
  std::shared_ptr<MusicPlayer> music_player_;
};

#endif  // CONTROLLER_CONTROLLER_H_
