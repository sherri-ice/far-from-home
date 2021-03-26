#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <memory>
#include <vector>

#include "GameObject/cat.h"
#include "player.h"

enum GameState {
  kGame,
  kMenu
};

class Model {
 public:
  Model();
  void LoadLevel(int level);

  Player* GetPlayer();
  std::vector<GameObject*> GetDrawableGameObjects() const;
  Cat* MakeCat();
  void SetGameState(int game_state);

 private:
  int current_level_ = 0;
  int game_state_ = GameState::kMenu;

  std::vector<Cat> cats_;
  Player* player_;
};

#endif  // MODEL_MODEL_H_
