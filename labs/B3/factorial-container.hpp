#ifndef FACTORIAL_CONTAINER_HPP
#define FACTORIAL_CONTAINER_HPP

#include <iterator>

class FactorialContainer
{
public:
  class Iterator: public std::iterator<std::bidirectional_iterator_tag, unsigned int>
  {
  public:
    static const size_t MIN_INDEX = 1;
    static const size_t MAX_INDEX = 11;

    Iterator();
    Iterator(size_t index);

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    const unsigned int& operator*() const;
    bool operator==(const Iterator& it) const;
    bool operator!=(const Iterator& it) const;

  private:
    size_t index_;
    unsigned int value_;
  };

  typedef std::reverse_iterator<Iterator> reverseIterator;

  Iterator begin() const;
  Iterator end() const;

  reverseIterator rbegin() const;
  reverseIterator rend() const;
};

#endif
