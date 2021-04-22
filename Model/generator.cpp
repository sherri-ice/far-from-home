#include <QFile>
#include "generator.h"
#include <QDebug>

std::mt19937 Generator::random_generator = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> random_id_generator(0, 0);


void Generator::GenerateTile(const Point&
left_corner) {
  int id = random_id_generator(random_generator);
  Tile new_tile(tiles_templates_.at(id));
  for (const auto& cat : new_tile.cats) {
    model_->MakeNewCat(cat.GetSize(),
                       cat.GetSpeed(),
                       cat.GetDrawPosition() + left_corner);
  }
  for (const auto& dog : new_tile.dogs) {
    model_->MakeNewDog(dog.GetSize(),
                       dog.GetSpeed(),
                       dog.GetDrawPosition() + left_corner,
                       dog.GetVisibilityRadius());
  }
}

void Generator::ParseTiles() {
  QString path(":/resourses/tiles_templates.json");
  QFile tiles_file(path);
  if (!tiles_file.open(QFile::ReadOnly)) {
    return;
  }
  QJsonObject
      json_object = QJsonDocument::fromJson(tiles_file.readAll()).object();

  QJsonArray tiles = json_object["tiles"].toArray();
  int size_of_templates = tiles.size();

  for (int i = 0; i < size_of_templates; ++i) {
    QJsonObject tile = tiles[i].toObject();
    QJsonArray objects = tile["objects"].toArray();
    Tile new_template;
    for (int j = 0; j < objects.size(); ++j) {
      QJsonObject object = objects[j].toObject();

      if (object["object_type"].toString() == "cat") {
        Size size(object["size"].toDouble(), object["size"].toDouble());
        Point point(object["point"].toObject()["x"].toDouble(),
                    object["point"].toObject()["y"].toDouble());
        new_template.cats.emplace_back(Cat(size,
                                           object["speed"].toDouble(),
                                           point));
      } else if (object["object_type"].toString() == "dog") {
        Size size(object["size"].toDouble(), object["size"].toDouble());
        Point point(object["point"].toObject()["x"].toDouble(),
                    object["point"].toObject()["y"].toDouble());
        new_template.dogs.emplace_back(Dog(size,
                                           object["speed"].toDouble(),
                                           point,
                                           object["visibility_radius"].toDouble()));
      }
    }
    tiles_templates_.push_back(new_template);
  }
}

void Generator::SetModel(const std::shared_ptr<Model>& model) {

  model_ = model;
}

void Generator::Clear() {
 // will erase templates
}

void Generator::GenerateMap() {
  ParseTiles();
  for (int x = 0; x < constants::kGameMapWidth; x += constants::kTileSize) {
    for (int y = 0; y < constants::kGameMapHeight; y += constants::kTileSize) {
      GenerateTile(Point(x, y));
    }
  }
}

