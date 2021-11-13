#include "rectangle.hpp"

#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>

#include "base-types.hpp"

li::Rectangle::Rectangle(double width, double height, const point_t &center) :
    corners{{ center.x + width / 2, center.y + height / 2 },
            { center.x - width / 2, center.y + height / 2 },
            { center.x - width / 2, center.y - height / 2 },
            { center.x + width / 2, center.y - height / 2 }}
{
  if (width <= 0.0)
  {
    throw std::invalid_argument("Incorrect rectangle's width: " + std::to_string(width) + "It can only be positive!");
  }

  if (height <= 0.0)
  {
    throw std::invalid_argument("Incorrect rectangle's height: " + std::to_string(height) + "It can only be positive!");
  }
}

double alferova::Rectangle::getWidth() const
{
  return alferova::getDistance(corners[2], corners[3]);
}

double alferova::Rectangle::getHeight() const
{
  return alferova::getDistance(corners[1], corners[2]);
}

alferova::point_t alferova::Rectangle::getPos() const
{
  return getFrameRect().pos;
}

double alferova::Rectangle::getArea() const
{
  return getWidth() * getHeight();
}

alferova::rectangle_t alferova::Rectangle::getFrameRect() const
{
  double xLeft = corners[0].x;
  double xRight = corners[0].x;
  double yUp = corners[0].y;
  double yDown = corners[0].y;

  for (size_t i = 1; i < 4; ++i)
  {
    xLeft = std::min(corners[i].x, xLeft);
    xRight = std::max(corners[i].x, xRight);
    yUp = std::max(corners[i].y, yUp);
    yDown = std::min(corners[i].y, yDown);
  }
  point_t pos{ ( xRight + xLeft ) / 2.0, ( yUp + yDown ) / 2.0 };
  return { xRight - xLeft, yUp - yDown, pos };
}

void alferova::Rectangle::move(const point_t &point)
{
  point_t center = getPos();
  move(point.x - center.x, point.y - center.y);
}

void alferova::Rectangle::move(double x, double y)
{
  for (size_t i = 0; i < 4; ++i)
  {
    corners[i].x += x;
    corners[i].y += y;
  }
}

void alferova::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument(
        "Incorrect value of the coefficient, it must be > 0 /n current value is: " + std::to_string(coefficient));
  }
  point_t center = getPos();
  double width = getWidth();
  double height = getHeight();
  width *= coefficient;
  height *= coefficient;
  corners[0] = { center.x + width / 2, center.y + height / 2 };
  corners[1] = { center.x - width / 2, center.y + height / 2 };
  corners[2] = { center.x - width / 2, center.y - height / 2 };
  corners[3] = { center.x + width / 2, center.y - height / 2 };
}

void alferova::Rectangle::rotate(double angle)
{
  angle = angle * ( M_PI / 180 );
  double cosA = cos(angle);
  double sinA = sin(angle);
  point_t center = getPos();
  for (size_t i = 0; i < 4; ++i)
  {
    double relativeX = corners[i].x - center.x;
    double relativeY = corners[i].y - center.y;
    corners[i].x = relativeX * cosA - relativeY * sinA + center.x;
    corners[i].y = relativeX * sinA + relativeY * cosA + center.y;
  }
}

void alferova::Rectangle::print(std::ostream &out) const
{
  out << "Rectangle: width: " << getWidth() << " height: " << getHeight() << " center: { " << getPos().x << " ; "
      << getPos().y << " }";
}
