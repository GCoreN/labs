#include <iostream>
#include <stdexcept>
#include <cstring>

#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid number of arguments.\n");
      return 1;
    }

    size_t pos = 0;
    const int task = std::stoi(argv[1], &pos);
    if (pos != strlen(argv[1]))
    {
      throw std::invalid_argument("Invalid number of task.\n");
      return 1;
    }
    switch (task)
    {
      case 1:
        task1(std::cin, std::cout);
        break;
      case 2:
        task2(std::cout);
        break;
      default:
        throw std::invalid_argument("Invalid number of task.\n");
        return 1;
    }
  }
  catch (const std::exception & exception)
  {
    std::cerr << exception.what();
    return 1;
  }

  return 0;
}
