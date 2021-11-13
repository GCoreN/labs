#ifndef LI_POLYGON
#define LI_POLYGON

#include <memory>
#include <initializer_list>
#include <iosfwd>

#include "base-types.hpp"
#include "shape.hpp"

namespace li
{
  class Polygon : public Shape
  {
  public:
    Polygon(const std::initializer_list<point_t> &array);
    Polygon(const Polygon &other);
    Polygon(Polygon &&other) noexcept;

    Polygon &operator=(const Polygon &other);
    Polygon &operator=(Polygon &&other) noexcept;
    point_t operator[](size_t index) const;

    size_t getSize() const;
    virtual point_t getPos() const override;
    virtual double getArea() const override;
    virtual rectangle_t getFrameRect() const override;

    virtual void move(const point_t &point) override;
    virtual void move(double x, double y) override;

    virtual void scale(double coefficient) override;

    virtual void rotate(double angle) override;

    virtual void print(std::ostream &out) const override;

  private:
    size_t size_;
    std::unique_ptr<point_t[]> points_;
  };
}

#endif
