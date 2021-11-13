#include "composite-shape.hpp"

#include <stdexcept>
#include <string>
#include <memory>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "base-types.hpp"

li::CompositeShape::CompositeShape(const std::shared_ptr<Shape> &shape) :
    size_(1),
    array_(std::make_unique<std::shared_ptr<Shape>[]>(size_))
{
  if (!shape)
  {
    throw std::invalid_argument("Invalid argument. Shape can't be null.");
  }

  array_[0] = shape;
}

li::CompositeShape::CompositeShape(const alferova::CompositeShape &other) :
    size_(other.size_),
    array_(std::make_unique<std::shared_ptr<Shape>[]>(size_))
{
  for (size_t i = 0; i < size_; i++)
  {
    array_[i] = other.array_[i];
  }
}

li::CompositeShape::CompositeShape(CompositeShape &&other) noexcept:
    size_(other.size_),
    array_(std::move(other.array_))
{
  other.size_ = 0;
}

li::CompositeShape &li::CompositeShape::operator=(CompositeShape &&other) noexcept
{
  if (this == &other)
  {
    return *this;
  }
  size_ = other.size_;
  array_.reset();
  array_ = std::move(other.array_);
  other.size_ = 0;
  return *this;
}

li::CompositeShape &li::CompositeShape::operator=(const CompositeShape &other)
{
  if (this == &other)
  {
    return *this;
  }
  size_ = other.size_;
  array_ = std::make_unique<std::shared_ptr<Shape>[]>(size_);
  for (size_t i = 0; i < size_; i++)
  {
    array_[i] = other.array_[i];
  }
  return *this;
}

std::shared_ptr<li::Shape> li::CompositeShape::operator[](size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Invalid argument. Index can't be more than size of the composite shape.");
  }
  return array_[index];
}

std::shared_ptr<const li::Shape> li::CompositeShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Invalid argument. Index can't be more than size of the composite shape.");
  }
  return array_[index];
}

size_t li::CompositeShape::getSize() const
{
  return size_;
}

void li::CompositeShape::add(const std::shared_ptr<Shape> &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Invalid argument. Shape can't be null.");
  }
  if (shape.get() == this)
  {
    throw std::invalid_argument("The shape can't be added to itself.");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> prevArray = std::move(array_);
  array_ = std::make_unique<std::shared_ptr<Shape>[]>(++size_);
  for (size_t i = 0; i < size_ - 1; i++)
  {
    array_[i] = prevArray[i];
  }
  array_[size_ - 1] = shape;
}

void li::CompositeShape::remove(size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Invalid argument. Index can't be more than size of the composite shape.");
  }

  if (size_ == 1)
  {
    throw std::out_of_range("The last shape can't be removed.");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> prevArray = std::move(array_);
  array_ = std::make_unique<std::shared_ptr<Shape>[]>(size_);

  for (size_t i = 0; i < size_; i++)
  {
    if (i > index)
    {
      array_[i - 1] = prevArray[i];
    }
    else if (i < index)
    {
      array_[i] = prevArray[i];
    }
  }

  --size_;
}

li::point_t li::CompositeShape::getPos() const
{
  return getFrameRect().pos;
}

double li::CompositeShape::getArea() const
{
  double area = 0;

  for (size_t i = 0; i < size_; i++)
  {
    area += array_[i]->getArea();
  }

  return area;
}

li::rectangle_t li::CompositeShape::getFrameRect() const
{
  rectangle_t frame = array_[0]->getFrameRect();
  double x = frame.pos.x, y = frame.pos.y;
  double dx = frame.width / 2.0, dy = frame.height / 2.0;
  double xLeft = x - dx;
  double xRight = x + dx;
  double yUp = y + dy;
  double yDown = y - dy;

  for (size_t i = 1; i < size_; i++)
  {
    frame = array_[i]->getFrameRect();
    x = frame.pos.x;
    y = frame.pos.y;
    dx = frame.width / 2.0;
    dy = frame.height / 2.0;
    xLeft = std::min(x - dx, xLeft);
    xRight = std::max(x + dx, xRight);
    yUp = std::max(y + dy, yUp);
    yDown = std::min(y - dy, yDown);
  }

  point_t pos{ ( xRight + xLeft ) / 2.0, ( yUp + yDown ) / 2.0 };

  return { xRight - xLeft, yUp - yDown, pos };
}

void li::CompositeShape::move(const point_t &point)
{
  point_t center = getFrameRect().pos;
  move(point.x - center.x, point.y - center.y);
}

void li::CompositeShape::move(double x, double y)
{
  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(x, y);
  }
}

void li::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument(
        "Incorrect value of the coefficient, it must be > 0 \n current value is: " + std::to_string(coefficient));
  }

  point_t center = getFrameRect().pos;
  double d = coefficient - 1;

  for (size_t i = 0; i < size_; i++)
  {
    point_t pos = array_[i]->getPos();
    double x = center.x - pos.x;
    double y = center.y - pos.y;
    array_[i]->scale(coefficient);
    array_[i]->move(x * d, y * d);
  }
}

void li::CompositeShape::rotate(double angle)
{
  double angleRad = angle * ( M_PI / 180 );
  double cosA = cos(angleRad);
  double sinA = sin(angleRad);
  point_t center = getPos();

  for (size_t i = 0; i < size_; i++)
  {
    double relativeX = array_[i]->getPos().x - center.x;
    double relativeY = array_[i]->getPos().y - center.y;
    array_[i]->move({ relativeX * cosA - relativeY * sinA + center.x, relativeX * sinA + relativeY * cosA + center.y });
    array_[i]->rotate(angle);
  }
}

void li::CompositeShape::print(std::ostream &out) const
{
  out << "Composite Shape consisting of: \n";
  for (size_t i = 0; i < getSize(); i++)
  {
    out << i << ". ";
    array_[i]->print(out);
    out << '\n';
  }

  out << '\n';
}
