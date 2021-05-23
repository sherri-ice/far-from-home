#include "rigid_body.h"
#include <iostream>
RigidBody::RigidBody(const Size* size, const Point* position) : object_size_
    (size), object_position_(position) {
}

Rect RigidBody::GetRect() const {
  double x = object_position_->GetX() - scale_coefficient_x_ *
      object_size_->GetWidth() / 2;
  double y = object_position_->GetY() + object_size_->GetHeight() / 2 -
      scale_coefficient_y_ * object_size_->GetHeight();
  return Rect{x, y, object_size_->GetWidth() * scale_coefficient_x_,
              object_size_->GetHeight() * scale_coefficient_y_};
}

bool RigidBody::IsCollide(const RigidBody& other_rigid_body) const {
  Rect other_rect = other_rigid_body.GetRect();
  Rect rect = GetRect();
  return Intersects(rect, other_rect);
}

void RigidBody::Draw(QPainter* painter, Resizer* resizer) const {
  auto rect = GetRect();
  auto game_size = Size(rect.width, rect.height);
  auto window_size = resizer->GameToWindowSize(game_size);
  auto game_coordinate = Point(rect.x, rect.y);
  auto window_coordinates = resizer->GameToWindowCoordinate(game_coordinate);
  painter->drawRect(static_cast<int>(window_coordinates.GetX()),
                    static_cast<int>(window_coordinates.GetY()),
                    static_cast<int>(window_size.GetWidth()),
                    static_cast<int>(window_size.GetHeight()));
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
  Rect new_rect = Rect{x, y, object_size_->GetWidth() * scale_coefficient_x_,
                       object_size_->GetHeight() * scale_coefficient_y_};
  return Intersects(new_rect, other_rigid_body.GetRect());
}

bool RigidBody::Intersects(const Rect& first_rect, const Rect& second_rect) {
  double bottom = first_rect.y + first_rect.height;
  double right = first_rect.x + first_rect.width;
  double other_bottom = second_rect.y + second_rect.height;
  double other_right = second_rect.x + second_rect.width;
  if (bottom < second_rect.y || other_bottom < first_rect.y || first_rect.x >
      other_right || second_rect.x > right) {
    return false;
  }
  return true;
}

Size RigidBody::GetVelocityToGoAround(const RigidBody& other_rigid_body,
                                      const Size& current_velocity, const
                                      Size& other_velocity) {
  Rect other_rect = other_rigid_body.GetRect();
  Border intersected_border = GetIntersectedBorder(other_rect);
  if (intersected_border == Border::kNone) {
    intersected_border = GetIntersectedBorderIfNone(other_rect);
  }
  if (intersected_border == border_which_is_collide_) {
    return saved_vector_to_get_around_;
  }
  border_which_is_collide_ = intersected_border;
  switch (border_which_is_collide_) {
    case Border::kTop: {
      if (current_velocity.GetHeight() < 0) {
        return current_velocity;
      }
      break;
    }
    case Border::kBottom: {
      if (current_velocity.GetHeight() > 0) {
        return current_velocity;
      }
      break;
    }
    case Border::kLeft: {
      if (current_velocity.GetWidth() < 0) {
        return current_velocity;
      }
      break;
    }
    case Border::kRight: {
      if (current_velocity.GetWidth() > 0) {
        return current_velocity;
      }
      break;
    }
    default: {
      break;
    }
  }
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
      auto velocity = Size(1, 0);
      if (current_velocity.GetWidth() < 0) {
        velocity.SetWidth(-1);
      }
      if (border_which_is_collide_ == Border::kTop && other_velocity
      .GetHeight() < 0 && velocity.GetWidth() * other_velocity.GetWidth() >
      0) {
        velocity.SetWidth(-1 * velocity.GetWidth());
      }
      if (border_which_is_collide_ == Border::kBottom && other_velocity
      .GetHeight() > 0 && velocity.GetWidth() * other_velocity.GetWidth() > 0) {
        velocity.SetWidth(-1 * velocity.GetWidth());
      }
      saved_vector_to_get_around_ = velocity;
      return velocity;
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
      auto velocity = Size(0, 1);
      if (current_velocity.GetHeight() < 0) {
        velocity.SetHeight(-1);
      }
      if (border_which_is_collide_ == Border::kRight && other_velocity
      .GetWidth() > 0 && other_velocity.GetHeight() * velocity.GetHeight() >
      0) {
        velocity.SetHeight(-1 * velocity.GetHeight());
      }
      if (border_which_is_collide_ == Border::kLeft && other_velocity
      .GetWidth() < 0 && other_velocity.GetHeight() * velocity.GetHeight() >
      0) {
        velocity.SetHeight(-1 * velocity.GetHeight());
      }
      saved_vector_to_get_around_ = velocity;
      return velocity;
    }
    default: {
      break;
    }
  }
  return current_velocity;
}

Border RigidBody::GetIntersectedBorder(const Rect& other_rect) const {
  if (GetRect().x >= other_rect.x + other_rect
  .width) {
    return Border::kRight;
  }
  if (GetRect().x + GetRect().width <= other_rect.x) {
    return Border::kLeft;
  }
  if (GetRect().y + GetRect().height <= other_rect.y) {
    return Border::kTop;
  }
  if (GetRect().y >= other_rect.y + other_rect.height) {
    return Border::kBottom;
  }
  return Border::kNone;
}

Rect RigidBody::GetRectInNewPosition(const Point& position) const {
  double x = position.GetX() - scale_coefficient_x_ *
      object_size_->GetWidth() / 2;
  double y = position.GetY() + object_size_->GetHeight() / 2 -
      scale_coefficient_y_ * object_size_->GetHeight();
  return Rect{x, y, object_size_->GetWidth() * scale_coefficient_x_,
              object_size_->GetHeight() * scale_coefficient_y_};
}

bool RigidBody::IsDestinationCollideWithRect(const Rect& rect) const {
  return Intersects(GetRect(), rect);
}

bool RigidBody::IfPointIsInsideBody(const Point& point) const {
  double x = point.GetX();
  double y = point.GetY();
  if (GetRect().x > x || GetRect().y > y || GetRect().x + GetRect().width < x
  || GetRect().y + GetRect().height < y) {
    return false;
  }
  return true;
}

Rect RigidBody::GetCollidedRect(const Rect& other_rect) const {
  auto rect = GetRect();
  double left = std::max(rect.x, other_rect.x);
  double top = std::max(rect.y, other_rect.y);
  double right = std::min(rect.x + rect.width, other_rect.x + other_rect.width);
  double bottom = std::min(rect.y + rect.height, other_rect.y + other_rect
  .height);
  double width = right - left;
  double height = bottom - top;
  return Rect{left, top, width, height};
}

bool RigidBody::IsCollide(const Rect& other_rect) const {
  return Intersects(GetRect(), other_rect);
}

Border RigidBody::GetIntersectedBorderIfNone(const Rect& other_rect) const {
  if (GetRect().x + constants::kIntersectedBorder >= other_rect.x + other_rect
      .width) {
    return Border::kRight;
  }
  if (GetRect().x + GetRect().width <= other_rect.x +
  constants::kIntersectedBorder) {
    return Border::kLeft;
  }
  if (GetRect().y + GetRect().height <= other_rect.y + constants::kIntersectedBorder) {
    return Border::kTop;
  }
  if (GetRect().y + constants::kIntersectedBorder >= other_rect.y +
  other_rect.height) {
    return Border::kBottom;
  }
  return Border::kNone;
}

// Size RigidBody::GetVectorToAvoidMovingCollision(const RigidBody& other_rigid_body,
//                                                 const Size& current_velocity) {
//   auto new_position = *object_position_ + current_velocity;
//   auto rect = GetRectInNewPosition(new_position);
//   auto collided_rect = other_rigid_body.GetCollidedRect(rect);
//   auto center_of_rect = Point(rect.x + rect.width / 2, rect.y + rect.height /
//   2);
//   Size direction_of_collision = center_of_rect.GetVectorTo(other_rigid_body
//       .GetCenterOfRigidBody());
//   Size velocity = Size(collided_rect.width, collided_rect.height);
//   Border intersected_border = GetIntersectedBorder(other_rigid_body.GetRect
//       ());
//   if (velocity.GetLength() > constants::kEpsilon) {
//     velocity /= velocity.GetLength();
//   }
//   if (border_which_is_collide_ == intersected_border) {
//     if (velocity.GetWidth() * saved_vector_to_get_around_.GetWidth() < 0) {
//       velocity.SetWidth(-1 * velocity.GetWidth());
//     }
//     if (velocity.GetHeight() * saved_vector_to_get_around_.GetHeight() < 0) {
//       velocity.SetHeight(-1 * velocity.GetHeight());
//     }
//     return saved_vector_to_get_around_;
//   }
//   // if (border_which_is_collide_ != intersected_border) {
//   //   need_to_get_around_ = false;
//   // } else if (need_to_get_around_) {
//   //   return saved_vector_to_get_around_;
//   // }
//   border_which_is_collide_ = intersected_border;
//
//   if (std::abs(current_velocity.GetWidth()) <
//   constants::kCheckIfVelocityIsCloseToZero) {
//     std::cout << "in width" << std::endl;
//     // if (need_to_get_around_) {
//     //   return saved_vector_to_get_around_;
//     // }
//     need_to_get_around_ = true;
//     if (current_velocity.GetHeight() < 0 && direction_of_collision.GetWidth
//         () <= 0) {
//       saved_vector_to_get_around_ = Size(velocity.GetWidth(), -velocity
//       .GetHeight());
//       return saved_vector_to_get_around_;
//     } else if (current_velocity.GetHeight() < 0) {
//       saved_vector_to_get_around_ = Size(-velocity.GetWidth(), -velocity
//       .GetHeight());
//       return saved_vector_to_get_around_;
//     } else if (direction_of_collision.GetWidth() >= 0) {
//       saved_vector_to_get_around_ = Size(-velocity.GetWidth(), velocity
//       .GetHeight());
//       return saved_vector_to_get_around_;
//     } else {
//       saved_vector_to_get_around_ = Size(velocity.GetWidth(), velocity
//       .GetHeight());
//       return saved_vector_to_get_around_;
//     }
//   }
//   if (std::abs(current_velocity.GetHeight()) <
//   constants::kCheckIfVelocityIsCloseToZero) {
//     std::cout << "in height " << std::endl;
//     need_to_get_around_ = true;
//     if (current_velocity.GetWidth() > 0 && direction_of_collision.GetHeight()
//     > 0) {
//       saved_vector_to_get_around_ = Size(velocity.GetWidth(), -velocity
//       .GetHeight());
//       return saved_vector_to_get_around_;
//     } else if (current_velocity.GetWidth() > 0) {
//       saved_vector_to_get_around_ = Size(velocity.GetWidth(), velocity.GetHeight());
//       return saved_vector_to_get_around_;
//     } else if (direction_of_collision.GetHeight() < 0) {
//       saved_vector_to_get_around_ = Size(-velocity.GetWidth(), velocity.GetHeight());
//       return saved_vector_to_get_around_;
//     } else {
//       saved_vector_to_get_around_ = Size(-velocity.GetWidth(), -velocity.GetHeight());
//       return saved_vector_to_get_around_;
//     }
//   }
//   need_to_get_around_ = false;
//   if (current_velocity.GetHeight() < 0) {
//     velocity.SetHeight(-velocity.GetHeight());
//   }
//   if (current_velocity.GetWidth() < 0) {
//     velocity.SetWidth(-velocity.GetWidth());
//   }
//   if (velocity.GetWidth() * direction_of_collision.GetWidth() > 0 && velocity
//   .GetHeight() * direction_of_collision.GetHeight() > 0) {
//     if (collided_rect.width > collided_rect.height) {
//       velocity.SetHeight(-1 * velocity.GetHeight());
//     } else {
//       velocity.SetWidth(-1 * velocity.GetWidth());
//     }
//   }
//   need_to_get_around_ = true;
//   saved_vector_to_get_around_ = velocity;
//   return velocity;
// }
