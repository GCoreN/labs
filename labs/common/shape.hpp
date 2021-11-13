#ifndef LI_SHAPE
#define LI_SHAPE

#include <iosfwd>

namespace li
{
  struct point_t;
  struct rectangle_t;

  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual point_t getPos() const = 0;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t &point) = 0;
    virtual void move(double x, double y) = 0;

    virtual void scale(double coefficient) = 0;

    virtual void rotate(double angle) = 0;

    virtual void print(std::ostream &out) const = 0;
  };
}

#endif
