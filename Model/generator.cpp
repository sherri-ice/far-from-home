#include <QFile>
#include "generator.h"

std::mt19937 Generator::random_generator = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int>
    random_id_generator(0, constants::kNumOfTilesTemplates - 1);

int Generator::GenerateId(const Point& left_corner) {
  // counts max coefficient of departure from the center, which affects
  // probability of generating boarder template
  double distancing_coeff =
      std::max(std::fabs(left_corner.GetX() / constants::kGameMapWidth),
               std::fabs(left_corner.GetY() / constants::kGameMapHeight));
  // let put coefficient in the power of 6, to reach smoothness
  distancing_coeff = std::pow(distancing_coeff, 6);

  // std::discrete_distribution<> generates different values according to
  // vector of probabilities, given to it
  // let's push border templates probabilities to the end of that vector
  int number_of_main_templates =
      constants::kNumOfTilesTemplates - constants::kNumOfBorderTemplates;
  // probability of generating main templates should be in inverse propotion
  // of probability of generating boarder templates
  // so let's make it 1 - distancing_coeff
  std::vector<double> probabilities
      (number_of_main_templates,
       1 - distancing_coeff);
  // adds probabilities of generating boarder templates
  auto border_templates_probabilities =
      std::vector<double>(constants::kNumOfBorderTemplates,
                          distancing_coeff);
  probabilities.insert(probabilities.end(), border_templates_probabilities
      .begin(), border_templates_probabilities.end());
  // initialization
  std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());
  int id = dist(random_generator);
  return id;
}

void Generator::GenerateTile(const Point&
left_corner) {
  int id = GenerateId(left_corner);
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
                       dog.GetVisibilityRadius(), dog.GetWalkingSpeed());
  }
  for (const auto& static_object : new_tile.static_objects) {
    model_->MakeNewPortal(static_object.GetSize(),
                          static_object.GetDrawPosition() + left_corner,
                          "",
                          true);
  }
  for (const auto& food : new_tile.food) {
    model_->MakeNewFood(food.GetSize(), food.GetDrawPosition() + left_corner);
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
        auto coordinates_array = object["point"].toArray();
        Point point(coordinates_array.at(0)["x"].toDouble(),
                    coordinates_array.at(0)["y"].toDouble());
        new_template.cats.emplace_back(Cat(size,
                                           object["speed"].toDouble(),
                                           point));
      }
      if (object["object_type"].toString() == "dog") {
        Size size(object["size"].toDouble(), object["size"].toDouble());
        auto coordinates_array = object["point"].toArray();
        Point point(coordinates_array.at(0)["x"].toDouble(),
                    coordinates_array.at(0)["y"].toDouble());
        double visibility_radius = object["visibility_radius"].toDouble();
        double walking_speed = object["walking_speed"].toDouble();
        new_template.dogs.emplace_back(Dog(size,
                                           object["speed"].toDouble(),
                                           point,
                                           visibility_radius, walking_speed));
      }
      if (object["object_type"].toString() == "static_object") {
        Size size(object["size"].toDouble(), object["size"].toDouble());
        auto coordinates_array = object["point"].toArray();
        Point point(coordinates_array.at(0)["x"].toDouble(),
                    coordinates_array.at(0)["y"].toDouble());
        new_template.static_objects.emplace_back(GameObject(size, point));
      }
      if (object["object_type"].toString() == "food") {
        Size size(object["size"].toDouble(), object["size"].toDouble());
        auto coordinates_array = object["point"].toArray();
        Point point(coordinates_array.at(0)["x"].toDouble(),
                    coordinates_array.at(0)["y"].toDouble());
        new_template.food.emplace_back(Food(size, point));
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
  for (int x = -constants::kGameMapWidth; x <= constants::kGameMapWidth;
       x += constants::kTileSize) {
    for (int y = -constants::kGameMapHeight; y <= constants::kGameMapHeight;
         y += constants::kTileSize) {
      GenerateTile(Point(x, y));
    }
  }
}
