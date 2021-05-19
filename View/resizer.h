#ifndef VIEW_RESIZER_H_
#define VIEW_RESIZER_H_

#include "../Model/point.h"
#include "../Model/constants.h"

class Resizer {
 public:
  void ChangeSystem(double window_width, double window_height);

  Point WindowToGameCoordinate(const Point& window_coordinate) const;
  Point GameToWindowCoordinate(const Point& game_coordinate) const;
  double GameToWindowLength(double length) const;
  double WindowToGameLength(double length) const;
  [[nodiscard]] Size GameToWindowSize(const Size& size) const;

  double ResizeLength(double length, int new_parameter) const;

  [[nodiscard]] Size GetGameSize() const;
  void Update(double radius, const Point& point);

 private:
  Size origin_offset_{0., 0.};
  double scaling_coefficient_ = 1;
  Size game_size_{constants::kGameWidth, constants::kGameHeight};
  int min_window_parameter_{};
};

#endif  // VIEW_RESIZER_H_
