#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <memory>

#include "Controller/abstract_controller.h"
#include "Model/model.h"
#include "View/view.h"

class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void Tick(int time) override;
  int GetCurrentTime() override;

  MovingObject* GetPlayer() override;

  void SetPlayerPosition(Point position) override;

 private:
  int current_game_time_{0};
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;
};

#endif  // CONTROLLER_CONTROLLER_H_
