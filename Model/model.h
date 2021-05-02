#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <list>
#include <memory>
#include <vector>
#include <map>
#include "../View/resizer.h"

#include "../GameObject/cat.h"
#include "../GameObject/dog.h"
#include "../GameObject/food.h"
#include "../GameObject/player.h"

enum GameState {
  kGame,
  kMenu
};

class Model {
 public:
  Model();
  void LoadLevel(int level);

  Player* GetPlayer();
  [[nodiscard]] std::vector<std::shared_ptr<GameObject>>
  GetDrawableGameObjects() const;
  void SetGameState(int game_state);
  std::shared_ptr<Cat> MakeNewCat(const Size& size,
                                  double speed,
                                  const Point& point);

  std::list<std::shared_ptr<Food>> GetFood();
  std::list<std::shared_ptr<Dog>> GetDogs();
  std::list<std::shared_ptr<Cat>> GetCats();

  void ClearObjects();

  void LoadAnimation();
  [[nodiscard]] std::vector<std::vector<QPixmap>> GetImagesByFramePath
      (const QString& path) const;

 private:
  std::map<QString, std::vector<std::vector<QPixmap>>> animations_;
  std::vector<std::vector<QPixmap>> objects_pics_{};
  int current_level_ = 0;
  int game_state_ = GameState::kMenu;

  std::list<std::shared_ptr<Cat>> cats_;
  Player* player_;
  std::list<std::shared_ptr<Food>> food_;
  std::list<std::shared_ptr<Dog>> dogs_;
};

#endif  // MODEL_MODEL_H_
