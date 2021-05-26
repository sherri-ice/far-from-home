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
    if (model_->GetCats().size() + 1 <= requested_cats_and_portals_) {
      model_->MakeNewCat(cat.GetSize(),
                         cat.GetSpeed(),
                         cat.GetDrawPosition() + left_corner);
    }
  }
  for (const auto& dog : new_tile.dogs) {
    model_->MakeNewDog(dog.GetSize(),
                       dog.GetSpeed(),
                       dog.GetDrawPosition() + left_corner,
                       dog.GetVisibilityRadius(), dog.GetWalkingSpeed());
  }
  for (const auto& static_object : new_tile.static_objects) {
    if (static_object.HasPortal()
        && current_true_portals_ + 1 > requested_cats_and_portals_) {
      break;
    }
    model_->MakeNewPortal(static_object.GetSize(),
                          static_object.GetDrawPosition() + left_corner,
                          static_object.HasPortal());
    if (static_object.HasPortal()) {
      ++current_true_portals_;
    }
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
        bool has_portal = object["has_portal"].toBool();
        Point point(coordinates_array.at(0)["x"].toDouble(),
                    coordinates_array.at(0)["y"].toDouble());
        new_template.static_objects.emplace_back(PortalObject(size, point));
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

void Generator::SetModel(const std::shared_ptr<Model>& model,
                         int requested_portals) {
  model_ = model;
  requested_cats_and_portals_ = requested_portals;
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
  GenerateTruePortals();
}

void Generator::GenerateTruePortals() {
  std::uniform_int_distribution<int>
      random_id_of_portal(0, model_->GetStaticObjects().size() - 1);
  int set_portals = 0;
  while (set_portals < requested_cats_and_portals_) {
    int id = random_id_of_portal(random_generator);
    while (model_->GetStaticObjects().at(id)->HasPortal()) {
      id = random_id_of_portal(random_generator);
    }
    model_->GetStaticObjects().at(id)->SetPortal();
    ++set_portals;
  }
}
