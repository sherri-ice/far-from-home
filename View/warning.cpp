#include <QFontMetrics>
#include <utility>

#include "warning.h"

Warning::Warning(QString message,
                 const Point& center,
                 double font_size, bool is_main_warning, bool supposed_to_fade,
                 int time_before_fade) : GameObject(Size(0, 0),
                                                               center),
                 message_(std::move(message)), font_size_(font_size),
                 is_main_warning_(is_main_warning),
                 supposed_to_fade_(supposed_to_fade),
                 time_before_fade_(time_before_fade), timer_() {
  if (supposed_to_fade_) {
    timer_.Start(time_before_fade_);
  }
}

void Warning::Tick(int delta_time) {
  if (is_drawn_) {
    timer_.Tick(delta_time);
  }

  if (timer_.IsTimeOut() && supposed_to_fade_) {
    if (text_color_.alpha() == 0) {
      is_dead_ = true;
    } else {
      if (background_color_.alpha() - fade_speed_ > 0) {
        background_color_.setAlpha(background_color_.alpha() - fade_speed_);
      }
      text_color_.setAlpha(text_color_.alpha() - fade_speed_);
    }
  }
}

void Warning::Draw(QPainter* painter, Resizer* resizer) const {
  if (is_drawn_) {
    painter->save();
    // QString family = QFontDatabase::applicationFontFamilies(0).at(0);
    double font_size = resizer->GameToWindowLength(font_size_);
    QFont font("Times New Roman", QFont::ExtraBold);
    // QFont font(family, QFont::ExtraBold);
    font.setPixelSize(font_size);
    painter->setFont(font);

    Point point;
    if (!is_main_warning_) {
      point = resizer->GameToWindowCoordinate(Point(
          position_.GetX() - font_size_ * message_.size() *
          warning_constants::kAlignCenter, position_.GetY() - font_size_));
    } else {
      double shift = resizer->GameToWindowLength(shift_);
      point = Point(position_.GetX() - font_size * message_.size() *
          warning_constants::kAlignCenter, position_.GetY() + shift -
          font_size);
    }

    QFontMetrics font_metrics = painter->fontMetrics();
    QRect rect = font_metrics.boundingRect(message_);
    painter->setBrush(QBrush(background_color_));
    painter->setPen(background_color_);
    painter->drawRect(point.GetX(), point.GetY() - font_size, rect.width(),
                      rect.height());
    painter->setPen(text_color_);
    painter->drawText(point.GetX(), point.GetY(), message_);
    painter->restore();
  }
}

void Warning::SetShift(int shift) {
  shift_ = shift;
}

void Warning::SetIfIsDrawn(bool is_drawn) {
  is_drawn_ = is_drawn;
}

double Warning::GetFontSize() const {
  return font_size_;
}

void Warning::UpdateMessage(const QString& message) {
  message_ = message;
}
