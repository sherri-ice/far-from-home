#include "portal_object.h"

std::mt19937 PortalObject::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());

PortalObject::PortalObject(const Size& size,
                           const Point& position,
                           const QString& skin_path) : GameObject(size,
                                                                  position) {
  skin_path_ = skin_path;
  warning_ = Warning("Click on a tree to send your cat on search",
                     Point(position.GetX(),
                           position.GetY() - size.GetHeight() / 2),
                     15);
  progress_bar_ = ProgressBar(position);
  warning_.SetIfIsDrawn(false);
  progress_bar_ = ProgressBar(position);
  std::uniform_int_distribution<>
      time(PortalConstants::kMinSearchTime, PortalConstants::kMaxSearchTime);
  search_time_ = time(random_generator_);
  progress_bar_.SetRange(0, search_time_);
  search_timer_.Start(search_time_);
}

void PortalObject::Draw(QPainter* painter, Resizer* resizer) const {
  rigid_body_.Draw(painter, resizer);
  painter->save();
  auto position = resizer->GameToWindowCoordinate(position_);
  auto size = resizer->GameToWindowSize(size_);
  painter->translate(position.GetX(), position.GetY());
  int width = static_cast<int>(size.GetWidth());
  int height = static_cast<int>(size.GetHeight());
  painter->drawPixmap(-width / 2, -height / 2, width, height, skin_);
  painter->restore();
  progress_bar_.Draw(painter, resizer);
  if (state_ != PortalState::kSearching) {
    warning_.Draw(painter, resizer);
  }
}

void PortalObject::Tick(int time) {
  switch (state_) {
    case PortalState::kWaitToSearch: {
      break;
    }
    case PortalState::kSearching: {
      if (!search_timer_.IsTimeOut()) {
        progress_bar_.IncCurrentValue(time);
        search_timer_.Tick(time);
      } else {
        state_ = PortalState::kFinishedSearch;
      }
      break;
    }
    case PortalState::kFinishedSearch: {
      warning_.UpdateMessage("Click on a tree to see the result!");
      progress_bar_.SetInvisible();
      search_timer_.Stop();
      state_ = PortalState::kWaitToSeeResult;
      break;
    }
    case PortalState::kWaitToSeeResult: {
      break;
    }
    case PortalState::kDefault:
    default: {
      break;
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
  if (state_ != PortalState::kWaitToSeeResult) {
    state_ = PortalState::kSearching;
    progress_bar_.SetVisible();
  }
}

bool PortalObject::IsCollected() {
  return (state_ == PortalState::kCollected);
}

bool PortalObject::HasPortal() const {
  return has_portal_;
}

void PortalObject::SetIfMessageIsShown(bool is_shown) {
  warning_.SetIfIsDrawn(is_shown);
}

int PortalObject::GetSearchTime() const {
  return search_time_;
}

void PortalObject::SetSearchTime(int search_time) {
  search_time_ = search_time;
}

bool PortalObject::ReadyToShowResult() {
  return (state_ == PortalState::kWaitToSeeResult);
}

void PortalObject::SetState(PortalState state) {
  state_ = state;
}

bool PortalObject::IsNotificationShown() {
  return  (state_ == PortalState::kNotificationShown);
}

void PortalObject::SetSuperSkin() {
  skin_ = QPixmap(":images/objects/portal.png");
}
