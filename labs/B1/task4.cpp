#include "tasks.hpp"

#include <random>
#include <vector>

#include "util.hpp"
#include "sort.hpp"

static void fillRandom(double *array, int size);

void task4(const char *direction, int size)
{
  if (direction == nullptr)
  {
    throw std::invalid_argument("Invalid sort direction.\n");
  }
  if (size < 1)
  {
    throw std::invalid_argument("Invalid array size.\n");
  }

  std::vector<double> vector(size);

  fillRandom(&vector[0], size);
  print(vector);

  sort<IteratorAccess>(vector, getDirection(direction));

  print(vector);
}

static void fillRandom(double *array, int size)
{
    static std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    for (int i = 0; i < size; i++)
    {
        array[i] = distribution(generator);
    }
}
