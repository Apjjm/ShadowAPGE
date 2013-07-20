#ifndef LOGGER_HPP
#define LOGGER_HPP
#include "coretypes.hpp"
namespace APGE
{

  class Logger
  {

  public:

    inline static void setErrorStream(std::ostream* stream)
    {
      mError = stream;
    }

    inline static void setWarnStream(std::ostream* stream)
    {
      mWarn = stream;
    }

    inline static void setInfoStream(std::ostream* stream)
    {
      mInfo = stream;
    }

    inline static std::ostream& error()
    {
      return *(mError);
    }

    inline static std::ostream& warn()
    {
      return *(mWarn);
    }

    inline static std::ostream& info()
    {
      return *(mInfo);
    }

  private:
    static std::ostream* mError;
    static std::ostream* mWarn;
    static std::ostream* mInfo;

    //Cannot instantiate this class!
    Logger();
    Logger(Logger& logger);
    Logger(Logger&& logger);
  };

}
#endif // LOGGER_HPP
