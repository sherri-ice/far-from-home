#include "dog.h"

Dog::Dog(const Size& size,
         double speed,
         const Point& position, double visibility_radius) :
         TargetMovingObject(size, speed, position), visibility_radius_
         (visibility_radius), home_position_(position) {
}

void Dog::Draw(QPainter* painter) const {
  rigid_body_.Draw(painter);
  painter->save();
  painter->translate(position_.GetX(), position_.GetY());
  int object_width = static_cast<int>(GetSize().GetWidth());
  int object_height = static_cast<int>(GetSize().GetHeight());
  if (is_visible_to_player_) {
    painter->drawEllipse(static_cast<int>(-visibility_radius_),
                         static_cast<int>(-visibility_radius_),
                         2 * static_cast<int>(visibility_radius_),
                         2 * static_cast<int>(visibility_radius_));
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
    SetDestination(reachable_cat_->GetPosition());
  } else {
    SetDestination(GetHomePosition());
  }
}

void Dog::Move(int delta_time) {
  MoveToDestination(delta_time);
}

void Dog::UpdateDogsAround(bool is_visible) {
  is_visible_to_player_ = is_visible;
}

bool Dog::CheckIfCanSeePlayer(const Point& player_position, double
  group_radius) {
  Size distance = position_.GetVectorTo(player_position);
  if (distance.GetLength() < group_radius + visibility_radius_) {
    return true;
  }
  return false;
}

Point Dog::GetHomePosition() const {
  return home_position_;
}

void Dog::SetReachableCat(const std::vector<std::shared_ptr<Cat>>& cats) {
  reachable_cat_ = nullptr;
  Size min_distance = Size(visibility_radius_, visibility_radius_);
  for (const auto& cat : cats) {
    Size cat_distance = position_.GetVectorTo(cat->GetPosition());
    if (CheckIfCanSeeCat(&(*cat)) &&
        cat_distance.GetLength() < min_distance.GetLength()) {
      reachable_cat_ = &(*cat);
      min_distance = cat_distance;
    }
  }
}

bool Dog::CheckIfCanSeeCat(const Cat* cat) const {
  Size distance = position_.GetVectorTo(cat->GetPosition());
  if (distance.GetLength() < visibility_radius_ +
      cat->GetSize().GetWidth() / 2) {
    return true;
  }
  return false;
}

