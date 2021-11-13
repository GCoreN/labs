#include "tasks.hpp"

#include <fstream>
#include <stdexcept>
#include <memory>
#include <vector>

#include "util.hpp"

void task2(const char *file)
{
  if (file == nullptr)
  {
    throw std::invalid_argument("Invalid sort direction.");
  }

  std::ifstream input(file);
  if (!input)
  {
    throw std::invalid_argument("Invalid filename.\n");
  }

  size_t size = 0;
  size_t capacity = 16;
  std::unique_ptr<char[]> array = std::make_unique<char[]>(capacity);

  while (input)
  {
    if (size == capacity)
    {
      capacity *= 2;
      std::unique_ptr<char[]> temp = std::move(array);
      array = std::make_unique<char[]>(capacity);
      std::copy(temp.get(), temp.get() + size, array.get());
    }

    input.read(&array[size], capacity - size);
    size += input.gcount();
  }

  if (!input.eof())
  {
    throw std::runtime_error("Error occurred while reading the file.\n");
  }

  std::vector<char> vector(array.get(), array.get() + size);

  print(vector, false);
}
