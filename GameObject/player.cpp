#include "player.h"

Player::Player(Size size, double speed, const Point& position) : MovingObject
(size, speed, position) {
  Cat main_cat(size, speed, position);
  cats_.push_back(main_cat);
}

void Player::SetPosition(const Point& position) {
  position_ = position;
  SetPositionForEachCat();
}

void Player::Move(int time) {
  for (auto &cat : cats_) {
    cat.Move(time);
  }
  position_ = cats_.at(0).GetPosition();
}

void Player::Draw(QPainter* painter) {
  for (auto &cat : cats_) {
    cat.Draw(painter);
  }
}

void Player::Tick(int time) {

}

void Player::SetPositionForEachCat() {
  cats_.at(0).SetPosition(position_);
  // Need to think about some algorithm that will set positions for other
  // cats, for them to be around central cat.
}

void Player::SetSpeed(double speed) {
  speed_ = speed;
  for (auto &cat : cats_) {
    cat.SetSpeed(speed);
  }
}

void Player::SetVelocity(Size velocity) {
  velocity_ = velocity;
  for (auto &cat : cats_) {
    cat.SetVelocity(velocity_);
  }
}
