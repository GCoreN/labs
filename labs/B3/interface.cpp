#include "interface.hpp"

#include <stdexcept>
#include <iostream>

Interface::Interface() :
  contacts_(),
  bookmarks_()
{
  bookmarks_.push_back({ "current", contacts_.begin() });
} 

void Interface::add(const std::string& name, const std::string& number)
{
  contacts_.push_back({ name, number });

  if (contacts_.begin() == std::prev(contacts_.end()))
  {
    bookmarks_.begin()->contact--;
  }
}

void Interface::insertBefore(const std::string& nameOfMark, const std::string& name, const std::string& number, std::ostream& out)
{
  if (contacts_.empty())
  {
    contacts_.push_back({ name, number });
    bookmarks_.begin()->contact = contacts_.begin();
  }

  bookmarksIterator it = findMark(nameOfMark);

  if (it == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }

  if (it->contact == contacts_.begin())
  {
    it->contact = contacts_.insert(contacts_.begin(), { name, number });
  }
  else
  {
    it->contact = contacts_.insert(it->contact, { name, number });
  }

}

void Interface::insertAfter(const std::string& nameOfMark, const std::string& name, const std::string& number, std::ostream& out)
{
  if (contacts_.empty()) {
    contacts_.push_back({ name, number });
    bookmarks_.begin()->contact = contacts_.begin();
  }

  bookmarksIterator it = findMark(nameOfMark);
  if (it == bookmarks_.end()) {
    out << "<INVALID BOOKMARK>\n";
    return;
  }

  it->contact = contacts_.insert(++it->contact, { name, number });
}

void Interface::deleteMark(const std::string& nameOfMark, std::ostream& out)
{
  bookmarksIterator bookmark = findMark(nameOfMark);

  if (bookmark == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }

   Phonebook::contactsIterator contact = bookmark->contact;

   for (bookmarksIterator it = bookmarks_.begin(); it != bookmarks_.end(); it++)
   {
     if (it->contact == contact)
     {
       if (it->contact == std::prev(contacts_.end()))
       {
         it->contact--;
       }
       else
       {
         it->contact++;
       }
     }
   } 
   contacts_.erase(contact);
}

void Interface::moveToDistance(const std::string& nameOfMark, int steps, std::ostream& out)
{
  bookmarksIterator bookmark = findMark(nameOfMark);

  if (bookmark == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }

  if (steps > 0)
  {
    for (int i = 0; i < steps; ++i)
    {
      if (bookmark->contact == std::prev(contacts_.end()))
      {
        bookmark->contact = contacts_.begin();
      }
      else
      {
        bookmark->contact++;
      }
    }
  }
  else
  {
    for (int i = 0; i > steps; --i)
    {
      if (bookmark->contact ==contacts_.begin())
      {
        bookmark->contact = std::prev(contacts_.end());
      }
      else
      {
        bookmark->contact--;
      }
    }
  }
}

void Interface::moveToFirst(const std::string& nameOfMark, std::ostream& out)
{
  bookmarksIterator bookmark = findMark(nameOfMark);

  if (bookmark == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }

  bookmark->contact = contacts_.begin();
}

void Interface::moveToLast(const std::string& nameOfMark, std::ostream& out)
{
  bookmarksIterator bookmark = findMark(nameOfMark);

  if (bookmark == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }

  bookmark->contact = std::prev(contacts_.end());
}

Interface::bookmarksIterator Interface::findMark(const std::string& markName)
{
  bookmarksIterator it = bookmarks_.begin();

  for (; it != bookmarks_.end(); ++it)
  {
    if (it->name == markName)
    {
      return it;
    }
  }
  return it;
}

void Interface::store(const std::string& firstMark, const std::string& newMark, std::ostream& out)
{
  bookmarksIterator bookmark = findMark(firstMark);
  if (bookmark == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }
  bookmarks_.push_back({ newMark, bookmark->contact });
}

void Interface::print(const std::string& nameOfMark, std::ostream& out)
{
  bookmarksIterator bookmark = findMark(nameOfMark);
  if (bookmark == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }

  if (contacts_.empty())
  {
    out << "<EMPTY>\n";
    return;
  }

  out << bookmark->contact->number << ' ' << bookmark->contact->name << '\n';
}
