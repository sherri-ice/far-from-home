#include "portal_object.h"

PortalObject::PortalObject(const Size& size,
                           const Point& position,
                           const QString& skin_path) : GameObject(size,
                                                                  position) {
  skin_path_ = skin_path;
  progress_bar_ = ProgressBar(position, size);
  progress_bar_.SetRange(0, 100);
  search_timer_ = Timer(1);
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

bool PortalObject::Search() {
  search_timer_.StartTimerWithRandom(100, 100);
  progress_bar_.SetVisible();
  while (!search_timer_.IsTimeOut()) {
    progress_bar_.IncCurrentValue();
  }
  progress_bar_.SetInvisible();
  return has_portal_;
}

void PortalObject::SetPortal() {
  has_portal_ = true;
}

void PortalObject::RemovePortal() {
  has_portal_ = false;
}

void PortalObject::Tick(int) {
}
