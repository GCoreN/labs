#include <iostream>
#include <cstring>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc < 2)
    {
      std::cerr << "Invalid number of arguments.\n";
      return 1;
    }
    if ((argv[1] == nullptr) || (sizeof(argv[1]) == 0))
    {
      std::cerr << "Enter number of the task.\n";
      return 1;
    }
    int num = 0;
    try
    {
      size_t pos = 0;
      num = std::stoi(argv[1], &pos);
      if (pos != std::strlen(argv[1]))
      {
       std::cerr << "Invalid number of the task.\n";
       return 1;
      }
    }
    catch(const std::exception& exception)
    {
      std::cerr << "Incorrect number of task! Enter number in range of 1 to 4.\n";
      return 1;
    }
    
    switch (num)
    {
    case 1:
      if (argc != 3)
      {
        std::cerr << "Invalid number of arguments. Sort direction required.\n";
        return 1;
      }
      if ((argv[2] == nullptr) || (sizeof(argv[2]) == 0))
      {
        std::cerr << "Invalid direction of sorting.\n";
        return 1;
      }
      try
      {
        task1(argv[2]);
      }
      catch(const std::runtime_error& exception)
      {
        std::cerr << exception.what() << '\n';
        return 1;
      }
      catch(const std::invalid_argument& exception)
      {
        std::cerr << exception.what() << '\n';
        return 1;
      }
      break;
    case 2:
      if (argc != 3)
      {
        std::cerr << "Invalid number of arguments. File name required.\n";
        return 1;
      }
      if ((argv[2] == nullptr) || (sizeof(argv[2]) == 0))
      {
        std::cerr << "File doesn't exist.\n";
        return 1;
      }
      try
      {
        task2(argv[2]);
      }
      catch(const std::invalid_argument& exception)
      {
        std::cerr << exception.what() << '\n';
        return 1;
      }
      catch(const std::runtime_error& exception)
      {
        std::cerr << exception.what() << '\n';
        return 1;
      }
      break;
    case 3:
      if (argc != 2)
      {
        std::cerr << "Invalid number of arguments. Only task number required.\n";
        return 1;
      }
      try
      {
        task3();
      }
      catch(const std::invalid_argument& exception)
      {
        std::cerr << exception.what() << '\n';
        return 1;
      }
      catch(const std::runtime_error& exception)
      {
        std::cerr << exception.what() << '\n';
        return 1;
      }
      break;
    case 4:
    {
      if (argc != 4)
      {
        std::cerr << "Invalid number of arguments. Sort direction and array size required.\n";
        return 1;
      }
      if ((argv[2] == nullptr) || (sizeof(argv[2]) == 0))
      {
        std::cerr << "Sort direction required.\n";
        return 1;
      }
      if ((argv[3] == nullptr) || (sizeof(argv[3]) == 0))
      {
        std::cerr << "Invalid number of arguments. Task 4 requires 2 arguments.\n";
        return 1;
      }
      int size = 0;
      try
      {
        size = std::stoi(argv[3]);
      }
      catch(const std::exception& exception)
      {
        std::cerr << "Invalid size of the array!\n";
        return 1;
      }
      try
      {
        task4(argv[2], size);
      }
      catch(const std::invalid_argument& exception)
      {
        std::cerr << exception.what() << '\n';
        return 1;
      }
      break;
    }
    default:
      std::cerr << "There is no task with such number!\n";
      return 1;
    }
  }
  catch (const std::exception &exception)
  {
    std::cerr << "Unknown error!\n";
    return 1;
  }

  return 0;
}
