#include "cat.h"

Cat::Cat(const Size& size, double speed, const Point& position) :
    MovingObject(size, speed, position) {
}

void Cat::Draw(QPainter* painter, Resizer* resizer) const {
    rigid_body_.Draw(painter, resizer);
    painter->save();
    auto position = resizer->GameToWindowCoordinate(position_);
    auto size = resizer->GameToWindowSize(size_);
//    object_animation_->Rescale(size);
    std::cout << "cat draw 1\n";
    painter->drawPixmap(position.GetX(),
                       position.GetY(), object_animation_->GetCurrentFrame());
    std::cout << "cat draw 2\n";
    painter->restore();
}

void Cat::Tick(int time) {
    if (is_moving_) {
        // todo catch keys and set animation road
        object_animation_->SetCurrentRoad(5);
    }
   object_animation_->Tick(time, is_moving_);
}

void Cat::Move(int time) {
  if (velocity_.GetLength() > constants::kEpsilon) {
      is_moving_ = true;
    velocity_ /= velocity_.GetLength();
    position_ += velocity_ * speed_ * time * constants::kTimeScale;
  } else {
      is_moving_ = false;
  }
}

void Cat::SetVelocityFromPlayer(Size velocity) {
  velocity_ = velocity;
}
