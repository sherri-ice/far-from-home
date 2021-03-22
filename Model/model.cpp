#include "model.h"

Model::Model(int level) : level_generator_(level), current_level_(level),
                          player_(Size(40, 40),
                                  0.,
                                  Point()) {
  player_.SetSpeed(level_generator_.GetPlayerSpeed());
}

void Model::SetPlayerPosition(Point position) {
  player_.SetPosition(position);
}

MovingObject* Model::GetPlayer() {
  return &player_;
}
