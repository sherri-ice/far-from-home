#include "dog.h"

Dog::Dog(const Size& size,
         double speed,
         const Point& position, double visibility_radius) : MovingObject
         (size, speed, position), visibility_radius_
    (visibility_radius), home_position_(position) {
  destination_ = home_position_;
}

void Dog::Draw(QPainter* painter, Resizer* resizer) const {
  rigid_body_.Draw(painter, resizer);
  painter->save();
  auto position = resizer->GameToWindowCoordinate(position_);
  auto size = resizer->GameToWindowSize(size_);
  painter->translate(position.GetX(), position.GetY());
  int object_width = static_cast<int>(size.GetWidth());
  int object_height = static_cast<int>(size.GetHeight());
  if (is_visible_to_player_) {
    Size radius = resizer->GameToWindowSize(Size(visibility_radius_,
                                                 visibility_radius_));
    painter->drawEllipse(static_cast<int>(-radius.GetWidth()),
                         static_cast<int>(-radius.GetHeight() *
                         constants::kSemiMinorCoefficient),
                         2 * static_cast<int>(radius.GetWidth()),
                         2 * static_cast<int>(radius.GetHeight() *
                         constants::kSemiMinorCoefficient));
  }
  painter->setBrush(Qt::black);
  painter->drawEllipse(-object_width / 2,
                       -object_height / 2,
                       object_width,
                       object_height);
  painter->restore();
}

void Dog::Tick(int delta_time) {
  if (reachable_cat_) {
    destination_ = reachable_cat_->GetDrawPosition();
  } else {
    destination_ = home_position_;
  }
  velocity_ = position_.GetVectorTo(destination_);
}

void Dog::Move(int delta_time) {
  if (velocity_.GetLength() > constants::kEpsilon) {
    velocity_ /= velocity_.GetLength();
    velocity_ *= delta_time * speed_ * constants::kTimeScale;
  }
  Size first_vector = (position_ + velocity_).GetVectorTo(destination_);
  Size second_vector = position_.GetVectorTo(destination_);
  if (first_vector.GetWidth() * second_vector.GetWidth() <=
      constants::kEpsilon && first_vector.GetHeight() * second_vector
      .GetHeight() <= constants::kEpsilon) {
    position_ = destination_;
  } else {
    position_ += velocity_;
  }
}

void Dog::SetIfItVisibleToPlayer(bool is_visible) {
  is_visible_to_player_ = is_visible;
}

void Dog::SetReachableCat(const std::vector<std::shared_ptr<Cat>>& cats) {
  reachable_cat_ = nullptr;
  Size min_distance = Size(visibility_radius_, visibility_radius_);
  for (const auto& cat : cats) {
    Size cat_distance = position_.GetVectorTo(cat->GetRigidPosition());
    if (CheckIfCanSeeCat(&(*cat)) &&
        cat_distance.GetLength() < min_distance.GetLength()) {
      reachable_cat_ = &(*cat);
      min_distance = cat_distance;
    }
  }
}

bool Dog::CheckIfCanSeeCat(const Cat* cat) const {
  return cat->GetRigidPosition().IsInEllipse(position_,
                                             visibility_radius_);
}
