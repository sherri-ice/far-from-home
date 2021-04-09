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

void Dog::Tick(int time) {
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
  auto needed_distance = group_radius + visibility_radius_;
  if (distance.GetLength() < needed_distance
      || (std::abs(distance.GetLength() - needed_distance)
          < constants::kEpsilon)) {
    return true;
  }
  return false;
}

Point Dog::GetHomePosition() const {
  return home_position_;
}
