#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include "APGE/Core/CoreTypes.hpp"
#include "IResourceHandler.hpp"
#include "TResourceHandler.hpp"

namespace APGE
{
  namespace Resource
  {
    class ResourceManager : sf::NonCopyable
    {
    public:
      ResourceManager()
      {
      }

      ~ResourceManager()
      {
        //Handle cleanup of all handlers
        std::map<const ResourceHandlerID, IResourceHandler*>::iterator iter;
        iter = handlers_.begin();

        while(iter != handlers_.end())
          {
            delete (iter->second);
            handlers_.erase(iter++);
          }
      }

      /**
       * @brief registerHandler - Register a handler. This object will take UNIQUE ownership of the handler and handle deletion!
       * @param handler - Should be a handler created with new [I.e. registerHandler(new(std::nothrow) SomeHandler);]
       * @return true if handler was registered without error
       */
      bool registerHandler(IResourceHandler* handler)
      {
        if(handler == 0)
          {
            LOGE("ResourceManager::registerHandler() - Handler was not constructed / invalid pointer.");
            return false;
          }
        ResourceHandlerID handlerID = handler->getHandlerID();

        //Check to see if resource handler is already registered
        std::map<const ResourceHandlerID, IResourceHandler*>::const_iterator iter;
        iter = handlers_.find(handlerID);
        if(iter != handlers_.end())
          {
            LOGE("ResourceManager::registerHandler() - Handler already registered!");
            return false;
          }

        //Add the handler
        handlers_.insert( std::pair<const ResourceHandlerID, IResourceHandler*>(
                           handlerID,handler ));
        return true;
      }

      /**
       * @brief getResourceHandler - Get a reference to the handler. Note: This reference will not expire until this object is destroyed.
       * @param handlerID - Unique Handler ID of the resource handler.
       * @return a reference to the resource handler.
       */
      IResourceHandler& getResourceHandler(const ResourceHandlerID handlerID) const
      {
        //Find the handler
        std::map<const ResourceHandlerID, IResourceHandler*>::const_iterator iter;
        iter = handlers_.find(handlerID);

        //Return a reference if handler found. Fatal error if not.
        assert((iter != handlers_.end()) && "ResourceManager::registerHandler() - Handler not registered!");
        return *(iter->second);
      }


      /**
       * @brief getResourceHandler - Get a reference to the handler. Note: This reference will not expire until this object is destroyed.
       * @return a reference to the resource handler.
       */
      template<class T> TResourceHandler<T>& getResourceHandler() const
      {
        //Find the handler
        std::map<const ResourceHandlerID, IResourceHandler*>::const_iterator iter;
        iter = handlers_.find(typeid(T).name());

        //Return a reference if handler found. Fatal error if not.
        assert((iter != handlers_.end()) && "ResourceManager::registerHandler() - Handler not registered!");

        return *(static_cast<TResourceHandler<T>*>(iter->second));
      }

    private:
      std::map<const ResourceHandlerID, IResourceHandler*> handlers_;


    };
  }
}
#endif
