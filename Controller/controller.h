#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <list>
#include <memory>

#include "Controller/abstract_controller.h"
#include "Model/model.h"
#include "View/view.h"

class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void StartGame(int level) override;
  void Tick(int time) override;
  int GetCurrentTime() override;

  Player* GetPlayer() override;

 private:
  void TickPlayer();
  void TickCats(int delta_time);
  void TickDogs(int delta_time);
  void TickFood(int delta_time);

  void CatsAndFoodIntersect();
  void PlayerAndStaticObjectsIntersect(const std::shared_ptr<Cat>& cat);
  void DogAndStaticObjectsIntersect(const std::shared_ptr<Dog>& dog, int
  delta_time);

  int current_game_time_{0};
  std::shared_ptr<Model> model_;
  std::shared_ptr<View> view_;
};

#endif  // CONTROLLER_CONTROLLER_H_
