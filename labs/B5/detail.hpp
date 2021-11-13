#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <map>

#include "base-types.hpp"

namespace detail
{
  bool isRectangle(const shape_t &shape);

  bool isSquare(const shape_t &shape);

  bool comparator(const shape_t &first, const shape_t &second);
}

#endif
