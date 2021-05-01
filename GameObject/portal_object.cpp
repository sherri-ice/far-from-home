#include "portal_object.h"

#include <iostream>

PortalObject::PortalObject(const Size& size,
                           const Point& position,
                           const QString& skin_path) : GameObject(size,
                                                                  position) {
  skin_path_ = skin_path;
  progress_bar_ = ProgressBar(position, size);
  progress_bar_.SetRange(0, 1000);
  search_timer_.StartTimerWithRandom(1000, 1000);
}

void PortalObject::Draw(QPainter* painter, Resizer* resizer) const {
  rigid_body_.Draw(painter, resizer);
  painter->save();
  auto position = resizer->GameToWindowCoordinate(position_);
  auto size = resizer->GameToWindowSize(size_);
  painter->setBrush(Qt::darkMagenta);
  painter->drawEllipse(position.GetX() - size.GetWidth() / 2,
                       position.GetY() - size.GetHeight() / 2,
                       size.GetWidth(),
                       size.GetHeight());
  painter->restore();
  progress_bar_.Draw(painter, resizer);
}

void PortalObject::Tick(int time) {
  if (is_searching_) {
    progress_bar_.SetVisible();
    if (!search_timer_.IsTimeOut()) {
      progress_bar_.IncCurrentValue();
      search_timer_.Tick(1);
    } else {
      progress_bar_.SetInvisible();
      SetDefaultState();
      search_timer_.Stop();
    }
  }
}

void PortalObject::SetPortal() {
  has_portal_ = true;
}

void PortalObject::RemovePortal() {
  has_portal_ = false;
}

void PortalObject::SetSearchState() {
  is_searching_ = true;
}

void PortalObject::SetDefaultState() {
  is_searching_ = false;
}
