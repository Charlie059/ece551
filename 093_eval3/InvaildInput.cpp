#include "InvaildInput.hpp"

const char * InvaildInput::what() const throw() {
  return error_msg;
}
