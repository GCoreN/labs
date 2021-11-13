#include "circle.hpp"

#include <cmath>
#include <stdexcept>
#include <string>
#include <iostream>

#include "base-types.hpp"

li::Circle::Circle(double radius, const point_t &center) :
    radius_(radius),
    center_(center)
{
  if (radius_ <= 0.0)
  {
    throw std::invalid_argument("Invalid circle's radius. " + std::to_string(radius) + " must be positive.");
  }
}

double li::Circle::getRadius() const
{
  return radius_;
}

li::point_t li::Circle::getPos() const
{
  return center_;
}

double li::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

li::rectangle_t li::Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2, center_ };
}

void li::Circle::move(const point_t &point)
{
  center_ = point;
}

void li::Circle::move(double x, double y)
{
  center_.x += x;
  center_.y += y;
}

void li::Circle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument(
        "Incorrect value of the coefficient, it must be > 0 \n current value is: " + std::to_string(coefficient));
  }
  radius_ *= coefficient;
}

void li::Circle::rotate(double)
{}

void li::Circle::print(std::ostream &out) const
{
  out << "Circle: radius: " << getRadius() << " center: { " << getPos().x << " ; " << getPos().y << " }";
}
