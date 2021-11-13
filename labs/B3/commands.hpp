#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include "interface.hpp"

void readCommand (Interface& phonebook, const std::string& command, std::ostream& out);

namespace commands
{
  void add(Interface& phonebook, std::istringstream& input, std::ostream& out);
  void store(Interface& phonebook, std::istringstream& input, std::ostream& out);
  void insert(Interface& phonebook, std::istringstream& input, std::ostream& out);
  void deleteMark(Interface& phonebook, std::istringstream& input, std::ostream& out);
  void print(Interface& phonebook, std::istringstream& input, std::ostream& out);
  void move(Interface& phonebook, std::istringstream& input, std::ostream& out);
}

#endif
