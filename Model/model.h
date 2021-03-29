#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <memory>
#include <vector>

#include "GameObject/cat.h"
#include "GameObject/food.h"
#include "GameObject/player.h"

enum GameState {
  kGame,
  kMenu
};

class Model {
 public:
  Model();
  void LoadLevel(int level);

  std::shared_ptr<Player> GetPlayer();
  std::vector<std::shared_ptr<GameObject>> GetDrawableGameObjects() const;
  void SetGameState(int game_state);

  void CreateFood();
  void DeleteFood(const std::shared_ptr<Food>& food);
  void IsFoodNear();

  std::list<std::shared_ptr<Food>>* GetFood();

  friend class GameObject;

 private:
  int current_level_ = 0;
  int game_state_ = GameState::kMenu;

  std::vector<Cat> cats_;
  std::shared_ptr<Player> player_;
  std::list<std::shared_ptr<GameObject>> objects_;
  std::list<std::shared_ptr<Food>> food_;
};

#endif  // MODEL_MODEL_H_
