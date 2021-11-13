#include "utils.hpp"

#include <istream>

std::istream &utils::skipSpaces(std::istream &input)
{
  while (std::isblank(input.peek()))
  {
    input.get();
  }
  return input;
}
