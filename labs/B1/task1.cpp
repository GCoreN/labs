#include "tasks.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <forward_list>

#include "sort.hpp"
#include "util.hpp"

void task1(const char *direction)
{
  if (direction == nullptr)
  {
    throw std::invalid_argument("Invalid sort direction.");
  }

  int n = 0;
  std::vector<int> vec;

  while (std::cin >> n)
  {
    vec.push_back(n);
  }

  if (!std::cin.eof())
  {
    throw std::runtime_error("Error of input!\n");
  }

  std::vector<int> vecCopy = vec;
  Direction dir = getDirection(direction);

  sort<IndexAccess>(vecCopy, dir);
  print(vecCopy);

  std::forward_list<int> list(vec.begin(), vec.end());

  sort<AtAccess>(vec, dir);
  print(vec);

  sort<IteratorAccess>(list, dir);
  print(list);
}
