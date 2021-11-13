#include "detail.hpp"

#include <vector>
#include <map>
#include <cmath>

bool detail::isRectangle(const shape_t &shape)
{
  if (shape.points_.size() != 4)
  {
    return false;
  }

  return pow((shape.points_[0].x_ - shape.points_[2].x_), 2) + pow((shape.points_[0].y_ - shape.points_[2].y_), 2) ==
    pow((shape.points_[1].x_ - shape.points_[3].x_), 2) + pow((shape.points_[1].y_ - shape.points_[3].y_), 2);
}


bool detail::isSquare(const shape_t &shape)
{
  if (!isRectangle(shape))
  {
    return false;
  }

  return ((abs(shape.points_[0].x_ - shape.points_[3].x_) == abs(shape.points_[0].y_ - shape.points_[1].y_)) &&
    (abs(shape.points_[0].x_ - shape.points_[3].x_) == abs(shape.points_[1].x_ - shape.points_[2].x_)));
}


bool detail::comparator(const shape_t &first, const shape_t &second)
{
  if (first.type_ == second.type_)
  {
    return first.points_.size() < second.points_.size();
  }

  return first.type_ < second.type_;
}
