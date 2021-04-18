#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <list>
#include <memory>
#include <vector>
#include <View/resizer.h>

#include "GameObject/cat.h"
#include "GameObject/dog.h"
#include "GameObject/food.h"
#include "GameObject/player.h"
#include "map.h"

enum GameState {
  kGame,
  kMenu
};

class Model {
 public:
  Model();

  void LoadMap();

  Player* GetPlayer();
  [[nodiscard]] std::vector<std::shared_ptr<GameObject>>
  GetDrawableGameObjects() const;
  void SetGameState(int game_state);

  std::list<std::shared_ptr<Food>> GetFood();
  std::list<std::shared_ptr<Dog>> GetDogs();
  std::list<std::shared_ptr<Cat>> GetCats();

  void ClearObjects();

 private:
  int game_state_ = GameState::kMenu;

  Player* player_;

  Map map_;
};

#endif  // MODEL_MODEL_H_
