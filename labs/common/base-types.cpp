#include "base-types.hpp"

#include <cmath>

bool li::isOverlapping(const li::rectangle_t &first, const li::rectangle_t &second)
{
  return (( first.pos.y + first.height / 2 > second.pos.y - second.height / 2 )
      || ( first.pos.y - first.height / 2 < second.pos.y + second.height / 2 ))
      && (( first.pos.x + first.width / 2 > second.pos.x - second.width / 2 )
          || ( first.pos.x - first.width / 2 < second.pos.x + second.width / 2 ));
}

double li::getDistance(const li::point_t &first, const li::point_t &second)
{
  return sqrt(( first.x - second.x ) * ( first.x - second.x ) + ( first.y - second.y ) * ( first.y - second.y ));
}
