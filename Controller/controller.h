#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <list>
#include <memory>

#include "Controller/abstract_controller.h"
#include "Model/model.h"
#include "View/view.h"

#include <Model/generator.h>

class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void StartGame() override;
  void Tick(int time) override;
  int GetCurrentTime() override;

  Player* GetPlayer() override;

  void ScanIfObjectWereClicked(const Point& point) override;

 private:
  void TickPlayer();
  void TickCats(int delta_time);
  void TickDogs(int delta_time);
  void TickFood(int delta_time);
  void TickObjects(int delta_time);
  void TickWarnings(int delta_time);
  void TickViewCircle();

  void CatsAndFoodIntersect();
  void MovingAndStaticObjectsIntersect(const std::shared_ptr<MovingObject>&
      moving_object);

  int current_game_time_{0};
  std::shared_ptr<Model> model_;
  std::shared_ptr<View> view_;
  Generator map_generator_;
};

#endif  // CONTROLLER_CONTROLLER_H_
