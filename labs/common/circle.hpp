#ifndef LI_CIRCLE
#define LI_CIRCLE

#include <iosfwd>

#include "shape.hpp"
#include "base-types.hpp"

namespace li
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t &center);

    double getRadius() const;
    double getArea() const override;
    point_t getPos() const override;
    rectangle_t getFrameRect() const override;

    void move(const point_t &point) override;
    void move(double x, double y) override;

    void scale(double coefficient) override;

    void rotate(double angle) override;

    void print(std::ostream &out) const override;

  private:
    double radius_;
    point_t center_;
  };
}

#endif
