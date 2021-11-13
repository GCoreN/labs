#ifndef GUARD_HPP
#define GUARD_HPP

#include <istream>

namespace utils
{
  class StreamGuard
  {
  public:
    StreamGuard(std::istream& input);
    ~StreamGuard();

  private:
    std::istream& stream_;
    std::istream::fmtflags flags_;
  };

}

#endif