#include "portal_object.h"

#include <iostream>

PortalObject::PortalObject(const Size& size,
                           const Point& position,
                           const QString& skin_path) : GameObject(size,
                                                                  position) {
  skin_path_ = skin_path;
  progress_bar_ = ProgressBar(position, size);
  progress_bar_.SetRange(0, 100);
  search_timer_.StartTimerWithRandom(100, 100);
  warning_ = Warning(position);
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
  warning_.Draw(painter, resizer);
}

void PortalObject::Tick(int time) {
  // if (state_ == PortalState::kDefault || state_ == PortalState::kCollected) {
  // }
  if (state_ == PortalState::kSearching) {
    if (!search_timer_.IsTimeOut()) {
      progress_bar_.IncCurrentValue();
      search_timer_.Tick(1);
    } else {
      state_ = PortalState::kPendingInfo;
      progress_bar_.SetInvisible();
      warning_.SetVisible();
      search_timer_.Stop();
    }
  }
  // if (state_ == PortalState::kPendingInfo) {
  //   // MakeIconWithInfo(has_portal_)
  //   state_ = PortalState::kCollected;
  // }
}

void PortalObject::SetPortal() {
  has_portal_ = true;
}

void PortalObject::RemovePortal() {
  has_portal_ = false;
}

void PortalObject::SetSearchState() {
  state_ = PortalState::kSearching;
  progress_bar_.SetVisible();
}

bool PortalObject::IsSearchComplete() {
  return (state_ == PortalState::kPendingInfo);
}

bool PortalObject::HasPortal() {
  return has_portal_;
}

