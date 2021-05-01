#include "rigid_body.h"

QRect RigidBody::GetRect() const {
  double x = object_position_->GetX() - scale_coefficient_x_ *
      object_size_->GetWidth() / 2;
  double y = object_position_->GetY() + object_size_->GetHeight() / 2 -
      scale_coefficient_y_ * object_size_->GetHeight();
  return QRect(static_cast<int>(x), static_cast<int>(y), static_cast<int>
  (object_size_->GetWidth() * scale_coefficient_x_), static_cast<int>
  (object_size_->GetHeight() * scale_coefficient_y_));
}

bool RigidBody::IsCollide(const RigidBody& other_rigid_body) const {
  return GetRect().intersects(other_rigid_body.GetRect());
}

void RigidBody::Draw(QPainter* painter, Resizer* resizer) const {
  auto rect = GetRect();
  auto game_size = Size(rect.width(), rect.height());
  auto window_size = resizer->GameToWindowSize(game_size);
  auto game_coordinate = Point(rect.x(), rect.y());
  auto window_coordinates = resizer->GameToWindowCoordinate(game_coordinate);
  rect.setX(window_coordinates.GetX());
  rect.setY(window_coordinates.GetY());
  rect.setWidth(window_size.GetWidth());
  rect.setHeight(window_size.GetHeight());
  painter->drawRect(rect);
}

RigidBody::RigidBody(const Size* size, const Point* position) : object_size_
  (size), object_position_(position) {
}

void RigidBody::SetScaleCoefficients(double coefficient_x,
                                     double coefficient_y) {
  scale_coefficient_x_ = coefficient_x;
  scale_coefficient_y_ = coefficient_y;
}

Point RigidBody::GetCenterOfRigidBody() const {
  double y = object_position_->GetY() + object_size_->GetHeight() / 2 -
      object_size_->GetHeight() * scale_coefficient_y_ / 2;
  return Point(object_position_->GetX(), y);
}

bool RigidBody::IfCollisionWillHappen(const RigidBody&
  other_rigid_body, const Size& velocity) const {
  Point new_center = *object_position_ + velocity;
  double x = new_center.GetX() - scale_coefficient_x_ *
      object_size_->GetWidth() / 2;
  double y = new_center.GetY() + object_size_->GetHeight() / 2 -
      scale_coefficient_y_ * object_size_->GetHeight();
  QRect object_rect = QRect(static_cast<int>(x), static_cast<int>(y),
                            static_cast<int>(object_size_->GetWidth() *
                            scale_coefficient_x_), static_cast<int>
                            (object_size_->GetHeight() * scale_coefficient_y_));
  return object_rect.intersects(other_rigid_body.GetRect());
}

Size RigidBody::GetVelocityToAvoidCollision(const RigidBody&
  other_rigid_body, const Size& current_velocity) {
  QRect other_rect = other_rigid_body.GetRect();
  if (std::abs(GetRect().y() + GetRect().height() - other_rect.y()) <
      constants::kCheckIfBordersAreClose) {
    if (need_to_get_around_ && border_which_is_collide_ == Border::kTop) {
      return saved_vector_to_get_around_;
    }
    border_which_is_collide_ = Border::kTop;
    if (current_velocity.GetHeight() < 0) {
      return current_velocity;
    }
  } else if (std::abs(other_rect.y() + other_rect.height() - GetRect().y()) <
      constants::kCheckIfBordersAreClose) {
    if (need_to_get_around_ && border_which_is_collide_ == Border::kBottom) {
      return saved_vector_to_get_around_;
    }
    border_which_is_collide_ = Border::kBottom;
    if (current_velocity.GetHeight() > 0) {
      return current_velocity;
    }
  } else if (std::abs(GetRect().x() + GetRect().width() - other_rect.x()) <
      constants::kCheckIfBordersAreClose) {
    if (need_to_get_around_ && border_which_is_collide_ == Border::kLeft) {
      return saved_vector_to_get_around_;
    }
    border_which_is_collide_ = Border::kLeft;
    if (current_velocity.GetWidth() < 0) {
      return current_velocity;
    }
  }
  if (std::abs(other_rect.x() + other_rect.width() - GetRect().x()) <
  constants::kCheckIfBordersAreClose) {
    if (need_to_get_around_ && border_which_is_collide_ == Border::kRight) {
      return saved_vector_to_get_around_;
    }
    border_which_is_collide_ = Border::kRight;
    if (current_velocity.GetWidth() > 0) {
      return current_velocity;
    }
  }
  need_to_get_around_ = false;

  switch (border_which_is_collide_) {
    case Border::kTop:
    case Border::kBottom: {
      if (std::abs(current_velocity.GetWidth()) <
      constants::kCheckIfVelocityIsCloseToZero) {
        need_to_get_around_ = true;
        if (GetCenterOfRigidBody().GetX() < other_rigid_body
            .GetCenterOfRigidBody().GetX()) {
          saved_vector_to_get_around_ = Size(-1, 0);
        } else {
          saved_vector_to_get_around_ = Size(1, 0);
        }
        return saved_vector_to_get_around_;
      }

      if (current_velocity.GetWidth() > 0) {
        return Size(1, 0);
      } else {
        return Size(-1, 0);
      }
    }
    case Border::kLeft:
    case Border::kRight: {
      if (std::abs(current_velocity.GetHeight()) <
      constants::kCheckIfVelocityIsCloseToZero) {
        need_to_get_around_ = true;
        if (GetCenterOfRigidBody().GetY() < other_rigid_body
            .GetCenterOfRigidBody().GetY()) {
          saved_vector_to_get_around_ = Size(0, -1);
        } else {
          saved_vector_to_get_around_ = Size(0, 1);
        }
        return saved_vector_to_get_around_;
      }

      if (current_velocity.GetHeight() > 0) {
        return Size(0, 1);
      } else {
        return Size(0, -1);
      }
    }
    default: {
      break;
    }
  }
  return current_velocity;
}
