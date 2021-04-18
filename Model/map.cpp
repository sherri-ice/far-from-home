#include "map.h"
#include <memory>

void Map::RandomlyMakeCat() {
  Point point = RandomizePoint();
  std::shared_ptr<Cat> cat = std::make_shared<Cat>(constants::kCatSize,
                                                   0.001, point);
  cats_.push_back(cat);
}

void Map::RandomlyMakeDog() {
  Point point = RandomizePoint();
  std::shared_ptr<Dog> dog = std::make_shared<Dog>(constants::kDogSize,
                                                   0.001, point, 100.);
  dogs_.push_back(dog);
}

void Map::RandomlyMakeFood() {
  Point point = RandomizePoint();
  std::shared_ptr<Food>
      food = std::make_shared<Food>(constants::kFoodSize, point);
  food_.push_back(food);
}

// it'll be smarter, i promise
void Map::MakeMap() {
  for (int i = 0; i < 1'000; ++i) {
    RandomlyMakeCat();
    RandomlyMakeDog();
    RandomlyMakeFood();
  }
}

Point Map::RandomizePoint() {
  return Point(rand() % constants::kGameMapWidth,
               rand() % constants::kGameMapHeight);
}


