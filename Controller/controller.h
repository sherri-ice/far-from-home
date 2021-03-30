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

  void StartGame(int level) override;
  void Tick(int time) override;
  int GetCurrentTime() override;

  Player* GetPlayer() override;

  void SetPlayerPosition(const Point& position) override;

  void RescaleObjects(const Resizer& resizer) override;

 private:
  int current_game_time_{0};
  std::shared_ptr<Model> model_;
  std::shared_ptr<View> view_;
};

#endif  // CONTROLLER_CONTROLLER_H_
