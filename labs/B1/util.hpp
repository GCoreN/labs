#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>

template <typename C>
void print(const C &container, bool allowSpaces = true)
{
  if (container.empty())
  {
    return;
  }

  for (typename C::const_iterator i = container.begin(); i != container.end(); i++)
  {
    std::cout << *i;
    if (allowSpaces)
    {
      std::cout << " ";
    }
  }
  if (allowSpaces)
  {
    std::cout << '\n';
  }
}

#endif
