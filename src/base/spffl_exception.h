#ifndef SPFFL_EXCEPTION_H
#define SPFFL_EXCEPTION_H

#include <exception>
#include <string>

namespace spffl {

class exception_t: public std::exception {
public:
  exception_t(const std::string& msg);
  virtual const char* what() const noexcept;
private:
  std::string msg;
};

} // namespace

#endif // SPFFL_EXCEPTION_H
