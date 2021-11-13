#include "sort.hpp"
#include <stdexcept>
#include <string.h>

Direction getDirection(const char *direction)
{
  if (direction == nullptr)
  {
    throw std::invalid_argument("Enter direction of sorting.\n");
  }

  if (strcmp(direction, "ascending") == 0)
  {
    return Direction::ACSENDING;
  }
  else if (strcmp(direction, "descending") == 0)
  {
    return Direction::DESCENDING;
  }
  else
  {
    throw std::invalid_argument("Invalid direction of the sorting.\n");
  }
}
