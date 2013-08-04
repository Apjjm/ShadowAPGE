#ifndef CORETYPES_HPP
#define CORETYPES_HPP

//Std
#include <memory>
#include <iostream>
#include <ostream>
#include "assert.h"

//Boost
#include "boost/filesystem.hpp"
//#include "boost/signals2.hpp"

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

  namespace Component
  {
    /**
     * @brief ComponentID - Type for lookup of componenets
     */
    typedef std::string ComponentType;

    /**
     * @brief ComponentHandlerID - Type for lookup of component handlers
     */
    typedef APGE::Resource::ResourceHandlerID ComponentHandlerID;

    class IComponent;
    class PositionComponent;
    class SpriteComponent;
  }

  namespace Entity
  {

    typedef std::string EntityID;

    class Entity;
  }

  namespace Messaging
  {
    class IMessageArguments;
    class ISubscriber;
    class IPublisher;

    enum MessageArgumentsType
    {
      MessageArgumentsTypeUnknown = 0
    };
  }

  namespace Script
  {
    class LuaState;
  }
}

//Forward Declarations


#endif // CORETYPES_HPP
