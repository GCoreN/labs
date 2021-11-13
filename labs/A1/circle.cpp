#include "circle.hpp"

#include <cmath>
#include <stdexcept>
#include <string>

#include "base-types.hpp"

Circle::Circle(double radius, const point_t& center) :
  center_(center)
{
  if (radius <= 0.0) //Проверка входных данных: радиус должен быть положителен, иначе кидаем исключение
  {
    throw std::invalid_argument("Wrong argument: " + std::to_string(radius)
        + " must be positive.");
  }

  radius_ = radius;
}

double Circle::getRadius() const
{
  return radius_;
}

point_t Circle::getPosition() const
{
  return center_;
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void Circle::move(const point_t& point)
{
  center_ = point;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
