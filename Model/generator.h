#ifndef GENERATOR_H
#define GENERATOR_H

#include <memory>
#include "model.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <random>

class Generator {

 public:
  Generator() = default;

  void GenerateMap();
  // void GenerateFood();
  void Clear();
  void SetModel(const std::shared_ptr<Model>& model);

 private:
  void GenerateTile(const Point& left_corner);
  void ParseTiles();
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
  static std::mt19937 random_generator;
};

#endif //GENERATOR_H
