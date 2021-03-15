#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <memory>
#include <QElapsedTimer>

#include "Controller/abstract_controller.h"
#include "Model/model.h"
#include "View/view.h"

class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void StartGame(int level) override;
  void EndGame() override;
  void Tick(int time) override;
  void ClickAction() override;
  void GameProcess() override;

  MovingObject* GetCat() override;

  void GenerateFood() override;

  int GetCurrentTime() override;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;

  int current_game_time_ = 0;
  QElapsedTimer game_start_time_;
};

#endif  // CONTROLLER_CONTROLLER_H_
