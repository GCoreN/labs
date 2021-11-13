#include "base-types.hpp"

#include <iostream>
#include <iterator>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "detail.hpp"
#include "stream-guard.hpp"
#include "utils.hpp"

std::istream & operator>>(std::istream &input, point_t &point)
{
  utils::StreamGuard guard(input);

  input >> std::noskipws;
  int x, y;
  char utilSymbol;

  if (!(input >> utils::skipSpaces >> utilSymbol))
  {
    return input;
  }

  if (input.peek() == EOF)
  {
    throw std::invalid_argument("invalid reading.");
  }

  if (utilSymbol != '(')
  {
    input.setstate(std::ios::failbit);
    return input.unget();
  }

  if (!(input >> utils::skipSpaces >> x >> utils::skipSpaces >> utilSymbol))
  {
    return input;
  }

  if (utilSymbol != ';')
  {
    input.setstate(std::ios::failbit);
    return input.unget();
  }

  if (!(input >> utils::skipSpaces >> y >> utils::skipSpaces >> utilSymbol))
  {
    return input;
  }

  if (utilSymbol != ')')
  {
    input.setstate(std::ios::failbit);
    return input.unget();
  }

  point = { x, y };

  return input;
}


std::ostream & operator<<(std::ostream &output, const point_t &point)
{
  output << '(' << point.x_ << ';' << point.y_ << ')';
  return output;
}


std::istream & operator>>(std::istream &input, shape_t &shape)
{
  utils::StreamGuard guard(input);
  input >> std::skipws;

  size_t topNum = 0;

  if (!(input >> topNum))
  {
    return input;
  }

  if (input.peek() == EOF)
  {
    throw std::invalid_argument("invalid reading.");
  }

  if (topNum < 3)
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  shape.points_.clear();
  std::vector<point_t> temp;
  std::copy_n(std::istream_iterator<point_t>(input), topNum, std::back_inserter(temp));

  shape.points_.swap(temp);

  if (shape.points_.size() == 3)
  {
    shape.type_ = ShapeType::TRIANGLE;
  }
  else if (detail::isSquare(shape))
  {
    shape.type_ = ShapeType::SQUARE;
  }
  else if (detail::isRectangle(shape))
  {
    shape.type_ = ShapeType::RECTANGLE;
  }
  else
  {
    shape.type_ = ShapeType::OTHER;
  }

  return input;
}


std::ostream & operator<<(std::ostream &output, const shape_t &shape)
{
  output << shape.points_.size() << ' ';

  auto it = shape.points_.begin();

  while (it != shape.points_.end())
  {
    output << *it << ' ';
    ++it;
  }

  return output;
}
