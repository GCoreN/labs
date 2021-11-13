#include "polygon.hpp"

#include <memory>
#include <stdexcept>
#include <cmath>
#include <initializer_list>
#include <iostream>

#include "base-types.hpp"

li::Polygon::Polygon(const std::initializer_list<li::point_t> &array) :
    size_(array.size()),
    points_(nullptr)
{
  if (size_ < 3)
  {
    throw std::invalid_argument("Invalid argument. At least 3 points required.");
  }

  points_ = std::make_unique<point_t[]>(size_);
  size_t i = 0;

  for (std::initializer_list<point_t>::const_iterator newPoint = array.begin(); newPoint != array.end(); newPoint++)
  {
    points_[i] = *newPoint;
    i++;
  }
}

li::Polygon::Polygon(const Polygon &other) :
    size_(other.size_),
    points_(std::make_unique<point_t[]>(size_))
{
  for (size_t i = 0; i < size_; ++i)
  {
    points_[i] = other.points_[i];
  }
}

li::Polygon::Polygon(Polygon &&other) noexcept:
    size_(other.size_),
    points_(std::move(other.points_))
{
  other.size_ = 0;
  other.points_ = nullptr;
}

li::Polygon &alferova::Polygon::operator=(const Polygon &other)
{
  if (this == &other)
  {
    return *this;
  }
  size_ = other.size_;
  points_.reset();
  points_ = std::make_unique<point_t[]>(size_);
  for (size_t i = 0; i < size_; ++i)
  {
    points_[i] = other.points_[i];
  }
  return *this;
}

li::Polygon &li::Polygon::operator=(Polygon &&other) noexcept
{
  size_ = other.size_;
  points_ = std::make_unique<point_t[]>(size_);
  points_ = std::move(other.points_);
  other.size_ = 0;
  other.points_ = nullptr;
  return *this;
}

li::point_t li::Polygon::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("There's no such point in the polygon!");
  }

  return points_[index];
}

size_t li::Polygon::getSize() const
{
  return size_;
}

li::point_t li::Polygon::getPos() const
{
  double xSum = 0.0;
  double ySum = 0.0;

  for (size_t i = 0; i < size_; ++i)
  {
    xSum += points_[i].x;
    ySum += points_[i].y;
  }

  return { xSum / size_, ySum / size_ };
}

double li::Polygon::getArea() const
{
  double area = 0.0;

  for (size_t i = 0; i < size_; ++i)
  {
    area += points_[i].x * points_[( i + 1 ) % size_].y - points_[i].y * points_[( i + 1 ) % size_].x;
  }

  return 0.5 * std::abs(area);
}

li::rectangle_t li::Polygon::getFrameRect() const
{
  double xLeft = points_[0].x;
  double xRight = points_[0].x;
  double yUp = points_[0].y;
  double yDown = points_[0].y;

  for (size_t i = 1; i < size_; i++)
  {
    xLeft = std::min(points_[i].x, xLeft);
    xRight = std::max(points_[i].x, xRight);
    yUp = std::max(points_[i].y, yUp);
    yDown = std::min(points_[i].y, yDown);
  }

  point_t pos{ ( xRight + xLeft ) / 2.0, ( yUp + yDown ) / 2.0 };

  return { xRight - xLeft, yUp - yDown, pos };
}

void li::Polygon::move(const point_t &point)
{
  point_t center = getPos();
  move(point.x - center.x, point.y - center.y);
}

void li::Polygon::move(double x, double y)
{
  for (size_t i = 0; i < size_; ++i)
  {
    points_[i].x += x;
    points_[i].y += y;
  }
}

void li::Polygon::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument(
        "Incorrect value of the coefficient, it must be > 0 \n current value is: " + std::to_string(coefficient));
  }

  point_t center = getPos();
  double d = coefficient - 1;

  for (size_t i = 0; i < size_; i++)
  {
    double x = center.x - points_[i].x;
    double y = center.y - points_[i].y;
    move(x * d, y * d);
  }
}

void li::Polygon::rotate(double angle)
{
  angle = angle * ( M_PI / 180 );

  double cosA = cos(angle);
  double sinA = sin(angle);
  point_t center = getPos();

  for (size_t i = 0; i < size_; i++)
  {
    double relativeX = points_[i].x - center.x;
    double relativeY = points_[i].y - center.y;
    points_[i].x = relativeX * cosA - relativeY * sinA + center.x;
    points_[i].y = relativeX * sinA + relativeY * cosA + center.y;
  }
}

void li::Polygon::print(std::ostream &out) const
{
  out << "Polygon consists of:\n";

  for (size_t i = 0; i < size_; ++i)
  {
    out << "( " << points_[i].x << " ; " << points_[i].y << " )\n";
  }
}
