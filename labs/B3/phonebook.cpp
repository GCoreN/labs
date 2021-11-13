#include "phonebook.hpp"

void Phonebook::push_back(const contact_t& contact)
{
  contacts_.push_back(contact);
}

bool Phonebook::empty()
{
  return contacts_.empty();
}

Phonebook::contactsIterator Phonebook::insert(contactsIterator pos, const contact_t& contact)
{
  return contacts_.insert(pos, contact);
}

Phonebook::contactsIterator Phonebook::erase(contactsIterator pos)
{
  return contacts_.erase(pos);
}

Phonebook::contactsIterator Phonebook::begin()
{
  return contacts_.begin();
}

Phonebook::contactsIterator Phonebook::end()
{
  return contacts_.end();
}
