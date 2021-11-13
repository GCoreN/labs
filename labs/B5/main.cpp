#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include "tasks.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: invalid number of provided arguments.\n";
    return 1;
  }

  int task = 0;
  size_t convertedNum = 0;

  try
  {
    task = std::stoi(argv[1], &convertedNum);
  }
  catch (std::invalid_argument &)
  {
    std::cerr << "Error: invalid task number.\n";
    return 1;
  }
  catch (std::out_of_range &)
  {
    std::cerr << "Error: task number is too large.\n";
    return 1;
  }

  if (convertedNum != std::strlen(argv[1]))
  {
    std::cerr << "Error: task number must consist only numbers.\n";
    return 1;
  }

  try
  {
    switch (task)
    {
      case 1 :
        tasks::task1();
        break;

      case 2 :
        tasks::task2();
        break;

      default :
        throw std::invalid_argument(" unknown number of task.");
    }
  }
  catch (const std::exception& exc)
  {
    std::cerr << "Error: " << exc.what() << '\n';
    return 1;
  }

  return 0;
}
