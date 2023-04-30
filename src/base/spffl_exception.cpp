#include "base/spffl_exception.h"

namespace spffl {

exception_t::exception_t(const std::string &msg) : msg(msg) {}

const char *exception_t::what() const noexcept { return this->msg.c_str(); }

} // namespace spffl
