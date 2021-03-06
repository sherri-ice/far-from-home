#ifndef MODEL_GENERATOR_H_
#define MODEL_GENERATOR_H_

#include <memory>
#include "model.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <random>
#include <algorithm>
#include <vector>

namespace constants {
const int kGameMapWidth = 7'000;
const int kGameMapHeight = 7'000;
const int kTileSize = 500;
const int kNumOfTilesTemplates = 10;
const int kNumOfBorderTemplates = 2;
}  // namespace constants

class Generator {
 public:
  Generator() = default;

  void GenerateMap();
  void Clear();
  void SetModel(const std::shared_ptr<Model>& model);

 private:
  void GenerateTile(const Point& left_corner);
  void ParseTiles();
  void GenerateCats();
  int GenerateId(const Point& left_corner);
  std::shared_ptr<Model> model_;
  class Tile {
   public:
    Tile() = default;
    std::vector<Cat> cats;
    std::vector<Dog> dogs;
    std::vector<Food> food;
    std::vector<GameObject> static_objects;
  };
  std::vector<Tile> tiles_templates_;
  int num_of_cats_{0};
  static std::mt19937 random_generator;
};

#endif  // MODEL_GENERATOR_H_
