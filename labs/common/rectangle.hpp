#ifndef LI_RECTANGLE
#define LI_RECTANGLE

#include <iosfwd>

#include "shape.hpp"
#include "base-types.hpp"

namespace li
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double height, const point_t &center);

    double getWidth() const;
    double getHeight() const;
    virtual point_t getPos() const override;
    virtual double getArea() const override;
    virtual rectangle_t getFrameRect() const override;

    virtual void move(const point_t &point) override;
    virtual void move(double x, double y) override;

    virtual void scale(double coefficient) override;

    virtual void rotate(double angle) override;

    virtual void print(std::ostream &out) const override;

  private:
    point_t corners[4];
  };
}

#endif
