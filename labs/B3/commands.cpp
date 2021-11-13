#include "commands.hpp"

#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <cctype>
#include <map>

namespace detail
{
  const std::map <std::string, void(*)(Interface&, std::istringstream&, std::ostream&)> commands{
      { "add", commands::add },
      { "store", commands::store },
      { "insert", commands::insert },
      { "delete", commands::deleteMark },
      { "show", commands::print },
      { "move", commands::move }
  };

  enum Position
  {
    AFTER,
    BEFORE
  };

  struct ReferenceToName
  {
    std::string& name;
  };

  struct ReferenceToCommand
  {
    std::string& command;
  };

  struct ReferenceToNumber
  {
    std::string& number;
  };

  struct ReferenceToBookmark
  {
    std::string& bookmark;
  };

  std::istringstream& operator>>(std::istringstream& input, ReferenceToCommand command);
  std::istringstream& operator>>(std::istringstream& input, Position& pos);
  std::istringstream& operator>>(std::istringstream& input, ReferenceToName name);
  std::istringstream& operator>>(std::istringstream& input, ReferenceToNumber number);
  std::istringstream& operator>>(std::istringstream& input, ReferenceToBookmark bookmark);

}

std::istringstream& detail::operator>>(std::istringstream& input, ReferenceToCommand command)
{
  input >> command.command;
  return input;
}

std::istringstream& detail::operator>>(std::istringstream& input, Position& pos)
{
  std::string pos;
  input >> pos;

  if (input.fail() || ((pos != "after") && (pos != "before")))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  
  if (pos == "after")
  {
    pos = Position::AFTER;
  }
  else
  {
    pos = Position::BEFORE;
  }

  return input;
}

std::istringstream& detail::operator>>(std::istringstream& input, ReferenceToName name)
{
  auto flag = input.flags();
  input >> std::ws;

  if (input.get() != '"')
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  input >> std::noskipws;
  std::string finalName = "";
  std::string tempName = "";

  while (std::getline(input, tempName, '"') && !input.eof())
  {
    finalName += tempName;

    if (finalName.back() == '\\')
    {
      finalName.back() = '"';
    }

    tempName = "";
  }

  if (input.eof())
  {
    if (tempName.empty())
    {
      input.clear();
    }
    else
    {
      for (size_t i = 0; i < tempName.size(); ++i)
      {
        if (!std::isspace(tempName[i]))
        {
          input.setstate(std::ios::failbit);
          return input;
        }
      }
      input.clear();
    }
  }

  name.name = finalName;
  input.setf(flag);

  return input;
}

std::istringstream& detail::operator>>(std::istringstream& input, ReferenceToNumber number)
{
  input >> number.number;

  if (number.number.empty())
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  const size_t numberSize = number.number.size();
  for (size_t i = 0; i < numberSize; ++i)
  {
    if (!std::isdigit(number.number[i]))
    {
      input.setstate(std::ios::failbit);
      return input;
    }
  }

  return input;
}

std::istringstream& detail::operator>>(std::istringstream& input, ReferenceToBookmark bookmark)
{
  input >> bookmark.bookmark;

  if (bookmark.bookmark.empty())
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  const size_t bookmarkSize = bookmark.bookmark.size();

  for (size_t i = 0; i < bookmarkSize; ++i)
  {
    if (!std::isalnum(bookmark.bookmark[i]) && (bookmark.bookmark[i] != '-'))
    {
      input.setstate(std::ios::failbit);
      return input;
    }
  }

  return input;
}

void readCommand(Interface& interface, const std::string& inputCommand, std::ostream& out)
{
  std::istringstream in{ inputCommand };
  std::string command;
  in >> detail::ReferenceToCommand{ command };
  
  if (!detail::commands.count(command))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  void (*commandFunc)(Interface&, std::istringstream&, std::ostream&) = detail::commands.at(command);
  commandFunc(interface, in, out);
}

void commands::add(Interface& interface, std::istringstream& input, std::ostream& out)
{
  std::string name;
  std::string contact;

  if (!(input >> detail::ReferenceToNumber{ contact } >> detail::ReferenceToName{ name }))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  interface.add(name, contact);
}

void commands::store(Interface& interface, std::istringstream& input, std::ostream& out)
{
  std::string firstMark;
  std::string newMark;

  if (!(input >> detail::ReferenceToBookmark{ firstMark } >> detail::ReferenceToBookmark{ newMark }))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  interface.store(firstMark, newMark, out);
}

void commands::insert(Interface& interface, std::istringstream& input, std::ostream& out)
{
  std::string name;
  std::string nameOfMark;
  std::string number;
  detail::Position position = detail::BEFORE;

  if (!(input >> position >> detail::ReferenceToBookmark{ nameOfMark }
        >> detail::ReferenceToNumber{ number } >> detail::ReferenceToName{ name }))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  switch (position)
  {
    case detail::AFTER:
      interface.insertAfter(nameOfMark, name, number, out);
      break;
    case detail::BEFORE:
      interface.insertBefore(nameOfMark, name, number, out);
      break;
  }
}

void commands::deleteMark(Interface& interface, std::istringstream& input, std::ostream& out)
{
  std::string nameOfMark;

  if (!(input >> detail::ReferenceToBookmark{ nameOfMark }))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  interface.deleteMark(nameOfMark, out);
}

void commands::print(Interface& interface, std::istringstream& input, std::ostream& out)
{
  std::string nameOfMark;

  if (!(input >> detail::ReferenceToBookmark{ nameOfMark }))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  interface.print(nameOfMark, out);
}

void commands::move(Interface& interface, std::istringstream& input, std::ostream& out)
{
  std::string nameOfMark;
  std::string steps;

  if (!(input >> detail::ReferenceToBookmark{ nameOfMark } >> steps))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  if (steps == "first")
  {
    interface.moveToFirst(nameOfMark, out);
  }
  else if (steps == "last")
  {
    interface.moveToLast(nameOfMark, out);
  } 
  else
  {
    int countOfSteps = 0;
    try
    {
      size_t pos = 0;
      countOfSteps = std::stoi(steps, &pos);

      if (pos != steps.length())
      {
        throw std::invalid_argument("<INVALID STEP>\n");
      }
    }
    catch (const std::exception& error) {
      out << "<INVALID STEP>\n";
      return;
    }
    interface.moveToDistance(nameOfMark, countOfSteps, out);
  }
}
