#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <list>
#include <memory>
#include <vector>
#include <View/resizer.h>
#include <GameObject/portal_object.h>

#include "GameObject/cat.h"
#include "GameObject/dog.h"
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

  Player* GetPlayer();
  std::vector<std::shared_ptr<GameObject>> GetDrawableGameObjects() const;
  void SetGameState(int game_state);
  std::shared_ptr<Cat> MakeNewCat(const Size& size,
                                  double speed,
                                  const Point& point);
  std::shared_ptr<PortalObject> MakeNewPortal(const Size& size,
                                              const Point& position,
                                              const QString& skin_path,
                                              bool has_portal);

  std::list<std::shared_ptr<Food>> GetFood();
  std::list<std::shared_ptr<Dog>> GetDogs();
  std::list<std::shared_ptr<Cat>> GetCats();
  std::list<std::shared_ptr<PortalObject>>& GetStaticObjects();
  void ClearObjects();

 private:
  int current_level_ = 0;
  int game_state_ = GameState::kMenu;

  std::list<std::shared_ptr<Cat>> cats_;
  Player* player_;
  std::list<std::shared_ptr<Food>> food_;
  std::list<std::shared_ptr<Dog>> dogs_;
  std::list<std::shared_ptr<PortalObject>> static_objects_;
};

#endif  // MODEL_MODEL_H_
