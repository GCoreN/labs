#ifndef LI_COMPOSITE_SHAPE
#define LI_COMPOSITE_SHAPE

#include <memory>
#include <iosfwd>

#include "shape.hpp"
#include "base-types.hpp"

namespace li
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> &shape);
    CompositeShape(const CompositeShape &other);
    CompositeShape(CompositeShape &&) noexcept;
    ~CompositeShape() = default;

    CompositeShape &operator=(const CompositeShape &other);
    CompositeShape &operator=(CompositeShape &&other) noexcept;
    std::shared_ptr<Shape> operator[](size_t index);
    std::shared_ptr<const Shape> operator[](size_t index) const;

    size_t getSize() const;
    virtual point_t getPos() const override;
    virtual double getArea() const override;
    virtual rectangle_t getFrameRect() const override;

    void move(const point_t &point) override;
    void move(double x, double y) override;

    void add(const std::shared_ptr<Shape> &shape);

    void remove(size_t index);

    void scale(double coefficient) override;

    void rotate(double angle) override;

    void print(std::ostream &out) const override;

  private:
    size_t size_;
    std::unique_ptr<std::shared_ptr<Shape>[]> array_;
  };
}

#endif
