#include "stream-guard.hpp"

#include <istream>

utils::StreamGuard::StreamGuard(std::istream &input) :
  stream_(input),
  flags_(input.flags())
{
}

utils::StreamGuard::~StreamGuard()
{
  stream_.setf(flags_);
}
