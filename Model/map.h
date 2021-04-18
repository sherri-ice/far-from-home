#ifndef MODEL_MAP_H_
#define MODEL_MAP_H_

#include <Model/point.h>
#include <GameObject/cat.h>
#include <GameObject/dog.h>
#include <GameObject/food.h>
#include <list>
#include <memory>

class Map {
 public:
  Map() = default;
  void RandomlyMakeCat();
  void RandomlyMakeDog();
  void RandomlyMakeFood();

  Point RandomizePoint();

  void MakeMap();

 private:
  std::list<std::shared_ptr<Cat>> cats_;
  std::list<std::shared_ptr<Food>> food_;
  std::list<std::shared_ptr<Dog>> dogs_;

  friend class Model;
};

#endif  // MODEL_MAP_H_
