#include "model.h"

// TODO(anyone)
// Model::Model() {
// }

void Model::SetModel(int level) {
  level_ = level;
  // TODO(anyone)
  // Наверное в классе Level будут изменяться константы в соответствии с
  // уровнем, а мы все, что надо будем получать из Level
  // Нужно будет передать level GameMap для ее генерации
}

void Model::ClearGameModel() {
  map_.ClearMap();
}

Cat* Model::GetCat() {
  return &cat_;
}
