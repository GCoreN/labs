#include "tasks.hpp"

#include <iostream>
#include <vector>
#include <iterator>

#include "util.hpp"

void task3()
{
  std::vector<int> vector;
  int number = 0;

  while ((std::cin >> number) && (number != 0))
  {
    vector.push_back(number);
  }

  if ((!std::cin && !std::cin.eof()) || (std::cin.eof() && (number != 0)))
  {
    throw std::runtime_error("Input error occurred.\n");
  }

  if (vector.empty())
  {
    return;
  }
  
  if (vector.back() == 1)
  {
    std::vector<int>::iterator insert_i = vector.begin();
    std::vector<int>::iterator i = vector.begin();

    while (i != vector.end())
    {
      if (*i % 2 != 0)
      {
        std::swap(*insert_i++, *i);
      }
      ++i;
    }

    vector.resize(std::distance(vector.begin(), insert_i));
  }

  if (vector.back() == 2)
  {
    std::vector<int>::iterator i = vector.begin();

    while (i != vector.end())
    {
      if (*i % 3 == 0)
      {
        i = vector.insert(++i, 3, 1);
        i += 2;
      }
      ++i;
    }
  }

  print(vector);
}
