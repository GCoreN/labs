#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <list>
#include <string>

class Phonebook
{
public:
  struct contact_t
  {
    std::string name;
    std::string number;
  };
  typedef std::list<contact_t>::iterator contactsIterator;

  void push_back(const contact_t& contact);
  bool empty();
  
  contactsIterator insert(contactsIterator pos, const contact_t& contact);
  contactsIterator erase(contactsIterator pos);
  contactsIterator begin();
  contactsIterator end();

private:
  std::list<contact_t> contacts_;
};

#endif
