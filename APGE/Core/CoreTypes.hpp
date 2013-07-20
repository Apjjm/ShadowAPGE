#ifndef CORETYPES_HPP
#define CORETYPES_HPP

//Std
#include <memory>
#include <iostream>
#include <ostream>
#include "assert.h"

//Boost
#include "boost/filesystem.hpp"

//SFML
#include "SFML_INCLUDES.hpp"


//LOGGING MACROS
#ifndef DEBUG_LOG
#define LOGD(x) do { APGE::Logger::info()<<"D:"<<x<<std::endl; } while(false)
#else
#define LOGD(x)
#endif

#define LOGI(x) do { APGE::Logger::info()<<"I:"<<x<<std::endl; } while(false)
#define LOGW(x) do { APGE::Logger::warn()<<"W:"<<x<<std::endl; } while(false)
#define LOGE(x) do { APGE::Logger::error()<<"E:"<<x<<std::endl; } while(false)
#define FATAL(x) do { APGE::Logger::error()<<"FATAL: "<<x<<std::endl; APGE::Application::getApplication().abort(EXIT_FAILURE); } while(false)
#define FATALC(x,y) do { APGE::Logger::error()<<"FATAL: "<<x<<std::endl; APGE::Application::getApplication().abort(y); } while(false)
#include "Logger.hpp"


//Asset core types
namespace APGE
{
  namespace Resource
  {

    /**
     * @brief ResourceHandlerID - Type for lookup of ResourceHandlers. unique id.
     */
    typedef std::string ResourceHandlerID;

    /**
     * @brief ResourceID - Type for lookup of resources. unique id.
     */
    typedef std::string ResourceID;

    /**
     * @brief The ResourceLoadMethod enum lists methods of loading resources from a source.
     */
    enum ResourceLoadMethod
    {
      ResourceLoadMethodUndefined = 0,
      ResourceLoadMethodFile = 1,
      ResourceLoadMethodMemory = 2,
      ResourceLoadMethodStream = 3
    };

  }
}



#endif // CORETYPES_HPP
