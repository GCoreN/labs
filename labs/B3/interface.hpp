#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <string>
#include <list>
#include <iosfwd>

#include "phonebook.hpp"

class Interface
{
public:
  Interface();

  void add(const std::string& name, const std::string& number);
  void insertBefore(const std::string& nameOfMark, const std::string& name, const std::string& number, std::ostream& out);
  void insertAfter(const std::string& nameOfMark, const std::string& name, const std::string& number, std::ostream& out);
  void deleteMark(const std::string& nameOfMark, std::ostream& out);
  
  void moveToDistance(const std::string& nameOfMark, int steps, std::ostream& out);
  void moveToLast(const std::string& nameOfMark, std::ostream& out);
  void moveToFirst(const std::string& nameOfMark, std::ostream& out);

  void store(const std::string& firstMark, const std::string& newMark, std::ostream& out);
  void print(const std::string& nameOfMark, std::ostream& out);

private:

  struct bookmark_t
  {
    std::string name;
    Phonebook::contactsIterator contact;
  };
  typedef std::list<bookmark_t>::iterator bookmarksIterator;

  Phonebook contacts_;
  std::list<bookmark_t> bookmarks_;

  bookmarksIterator findMark(const std::string& markName);  //returns bookmark's end if not found 
};

#endif
