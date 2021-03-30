#include "food.h"

enum Meal {
  FISH,
  BURGER,
  SAUSAGE,
  PIZZA,
  SUSHI
};

Food::Food() : GameObject(Size(20, 20), Point(0, 0)) {
  meal_ =  rand() % ((5 + 1) - 1) + 1;
  int x = (rand() % (1000));
  int y = (rand() % (1000));
  position_ = Point(x, y);
  SetRect(position_, size_);
}

void Food::Draw(QPainter* painter) const {
  painter->save();
  auto position = position_;
  painter->drawRect(rect_);
  painter->translate(position.GetX(), position.GetY());
  switch (meal_) {
    case FISH: {
      painter->setBrush(Qt::blue);
      break;
    } case BURGER: {
      painter->setBrush(Qt::yellow);
      break;
    } case SAUSAGE: {
      painter->setBrush(Qt::darkMagenta);
      break;
    } case PIZZA: {
      painter->setBrush(Qt::lightGray);
      break;
    } case SUSHI: {
      painter->setBrush(Qt::darkGreen);
      break;
    } default: {
      painter->setBrush(Qt::darkGreen);
      break;
    }
  }
  int width = static_cast<int>(GetSize().GetWidth());
  int height = static_cast<int>(GetSize().GetHeight());
  painter->drawEllipse(-width / 2, -height / 2, width, height);
  painter->restore();
}

void Food::Tick(int time) {
}
