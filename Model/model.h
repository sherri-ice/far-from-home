#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <memory>
#include <list>
#include "GameObject/cat.h"
#include "Model/game_map.h"
#include "Model/level.h"

class Model {
 public:
  Model() = default;
  ~Model() = default;

  void SetModel(int level);
  void ClearGameModel();

  Cat* GetCat();

 private:
  // TODO(anyone)
  // void LoadLevel();
  std::list<std::shared_ptr<Cat>> cats_;
  int level_;
  double visibility_radius_;

  GameMap map_;
  Level current_level_;

  Cat cat_;
};

#endif  // MODEL_MODEL_H_
