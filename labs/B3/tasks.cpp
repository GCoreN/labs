#include "tasks.hpp"
#include <iostream>
#include <algorithm>
#include "factorial-container.hpp"
#include "phonebook.hpp"
#include "commands.hpp"

void task1(std::istream& in, std::ostream& out)
{
  Interface phonebook;
  std::string command;
  while (std::getline(in, command))
  {
    readCommand(phonebook, command, out);
  }
  if (!in.eof())
  {
    throw std::runtime_error("Error occurred while reading.");
  }
}

void task2(std::ostream& out)
{
  FactorialContainer factorial;

  std::copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(out, " "));
  out << '\n';

  std::reverse_copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(out, " "));
  out << '\n';
}
