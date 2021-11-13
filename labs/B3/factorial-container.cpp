#include "factorial-container.hpp"

#include <stdexcept>

FactorialContainer::Iterator::Iterator() :
  index_ { 1 },
  value_ { 1 } 
{}

FactorialContainer::Iterator::Iterator(size_t index) :
  index_ { index },
  value_ { 1 }
{
  if ((index < MIN_INDEX) || (index > MAX_INDEX))
  {
    throw std::out_of_range("Invalid index of factorial");
  }

  for (size_t i = 1; i <= index; ++i)
  {
    value_ *= i;
  }
}

FactorialContainer::Iterator& FactorialContainer::Iterator::operator++()
{
  ++index_;
  if (index_ > MAX_INDEX)
  {
    throw std::out_of_range("Invalid index of factorial");
  }

  value_ *= index_;
  return *this;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++(*this);
  return temp;
}

FactorialContainer::Iterator& FactorialContainer::Iterator::operator--()
{
  --index_;
  if (index_ < MIN_INDEX)
  {
    throw std::out_of_range("Index of factorial must be in range [1, 10]");
  }

  value_ /= (index_ + 1);
  return *this;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator--(int)
{
  Iterator temp = *this;
  --(*this);
  return temp;
}

const unsigned int& FactorialContainer::Iterator::operator*() const
{
  return value_;
}

bool FactorialContainer::Iterator::operator==(const Iterator& it) const
{
  return value_ == it.value_;
}

bool FactorialContainer::Iterator::operator!=(const Iterator& it) const
{
  return value_ != it.value_;
}

FactorialContainer::Iterator FactorialContainer::begin() const
{
  return Iterator::MIN_INDEX;
}

FactorialContainer::Iterator FactorialContainer::end() const
{
  return Iterator::MAX_INDEX;
}

FactorialContainer::reverseIterator FactorialContainer::rbegin() const
{
  return std::make_reverse_iterator(end());
}

FactorialContainer::reverseIterator FactorialContainer::rend() const
{
  return std::make_reverse_iterator(begin());
}
