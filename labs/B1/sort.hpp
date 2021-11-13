#ifndef SORTING_HPP
#define SORTING_HPP

#include <string.h>
#include <stdexcept>
#include <functional>

#include "strategies.hpp"

enum struct Direction
{
  ACSENDING,
  DESCENDING
};

Direction getDirection(const char *direction);

template <template <typename C> typename Access, typename C>
void sort(C &values, Direction direction)
{
  using reference_type = typename C::reference;

  std::function<bool(reference_type, reference_type)> comparator;
  if (direction == Direction::ACSENDING)
  {
    comparator = std::greater<reference_type>();
  }
  else
  {
    comparator = std::less<reference_type>();
  }

  for (auto i = Access<C>::begin(values); i != Access<C>::end(values); ++i) // size_t for Index and Iterator Access, C::iterator for Iterator Access
  {
    auto temp = i;
    for (auto j = Access<C>::next(i); j != Access<C>::end(values); ++j)
    {
      if (comparator(Access<C>::element(values, temp), Access<C>::element(values, j)))
      {
        temp = j;
      }
    }
    if (temp != i)
    {
      std::swap(Access<C>::element(values, temp), Access<C>::element(values, i));
    }
  }
}

#endif
