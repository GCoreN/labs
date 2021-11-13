#include "rectangle.hpp"

#include <stdexcept>
#include <string>

#include "base-types.hpp"

Rectangle::Rectangle(double width, double height, const point_t& center) :
  rec_{ width, height, center }
{
  if (width <= 0.0 || height <= 0.0) //Проверка входных данных: ширина и высота должны быть положительны, иначе кидаем исключение
  {
    throw std::invalid_argument("Wrong argument: " + std::to_string(width)
        + " must be positive.");
  }
}

double Rectangle::getWidth() const
{
  return rec_.width;
}

double Rectangle::getHeight() const
{
  return rec_.height;
}

point_t Rectangle::getPosition() const
{
  return rec_.pos;
}

double Rectangle::getArea() const
{
  return rec_.width * rec_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rec_;
}

void Rectangle::move(const point_t& point)
{
  rec_.pos = point;
}

void Rectangle::move(double dx, double dy)
{
  rec_.pos.x += dx;
  rec_.pos.y += dy;
}
