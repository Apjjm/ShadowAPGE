#include "Logger.hpp"

namespace APGE
{
  std::ostream* Logger::mError = &(std::cerr);
  std::ostream* Logger::mWarn = &(std::cout);
  std::ostream* Logger::mInfo = &(std::cout);
}
