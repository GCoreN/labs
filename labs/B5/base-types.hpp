#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

#include <vector>
#include <iostream>

struct point_t
{
  int x_, y_;
};

enum class ShapeType
{
  TRIANGLE,
  SQUARE,
  RECTANGLE,
  OTHER
};

struct shape_t
{
  std::vector<point_t> points_;
  ShapeType type_;
};

std::istream & operator>>(std::istream &input, point_t &point);
std::ostream & operator<<(std::ostream &output, const point_t &point);

std::istream & operator>>(std::istream &input, shape_t &shape);
std::ostream & operator<<(std::ostream &output, const shape_t &shape);

#endif
