#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <memory>
#include <list>

#include "GameObject/cat.h"
#include "GameObject/player.h"
#include "Model/level_generator.h"

class Model {
 public:
  explicit Model(int level = 0);

  MovingObject* GetPlayer();
  void SetPlayerPosition(Point position);

 private:
  LevelGenerator level_generator_;
  int current_level_;

  std::list<std::shared_ptr<Cat>> cats_;

  Player player_;
};

#endif  // MODEL_MODEL_H_
