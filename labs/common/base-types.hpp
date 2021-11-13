#ifndef LI_BASE_TYPES
#define LI_BASE_TYPES

namespace li
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };

  bool isOverlapping(const rectangle_t &first, const rectangle_t &second);

  double getDistance(const point_t &first, const point_t &second);
}

#endif
