#ifndef STRATEGIES_HPP
#define STRATEGIES_HPP

#include <iostream>

template <typename C>
struct IndexAccess
{
  static typename C::reference element(C &container, size_t i)
  {
    return container[i];
  }
  static size_t begin(const C &)
  {
    return 0;
  }
  static size_t end(const C &container)
  {
    return container.size();
  }
  static size_t next(size_t i)
  {
    return ++i;
  }
};

template <typename C>
struct AtAccess
{
  static typename C::reference element(C &container, size_t i)
  {
    return container.at(i);
  }
  static size_t begin(const C &)
  {
    return 0;
  }
  static size_t end(const C &container)
  {
    return container.size();
  }
  static size_t next(size_t i)
  {
    return ++i;
  }
};

template <typename C>
struct IteratorAccess
{
  static typename C::reference element(C &, typename C::iterator i)
  {
    return *i;
  }
  static typename C::iterator begin(C &container)
  {
    return container.begin();
  }
  static typename C::iterator end(C &container)
  {
    return container.end();
  }
  static typename C::iterator next(typename C::iterator i)
  {
    return ++i;
  }
};

#endif
