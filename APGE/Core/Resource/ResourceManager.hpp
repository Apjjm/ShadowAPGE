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
      }

      /**
       * @brief registerHandler
       * @param handler
       * @return true if handler was registered without error
       */
      bool registerHandler(std::shared_ptr<IResourceHandler> handler)
      {
        if(handler == 0)
          {
            LOGE("ResourceManager::registerHandler() - Handler was not constructed / invalid pointer.");
            return false;
          }
        ResourceHandlerID handlerID = handler->getHandlerID();

        //Check to see if resource handler is already registered
        std::map<const ResourceHandlerID, std::shared_ptr<IResourceHandler>>::const_iterator iter;
        iter = handlers_.find(handlerID);
        if(iter != handlers_.end())
          {
            LOGE("ResourceManager::registerHandler() - Handler already registered!");
            return false;
          }

        //Add the handler
        handlers_.insert(std::pair<const ResourceHandlerID,std::shared_ptr<IResourceHandler>>(
                           handlerID,handler ));
        return true;
      }

      /**
       * @brief getResourceHandler - Get a shared_pointer to the handler.
       * @param handlerID - Unique Handler ID of the resource handler.
       * @return a shared_pointer to the resource handler.
       */
      std::shared_ptr<IResourceHandler> getResourceHandler(const ResourceHandlerID handlerID) const
      {
        //Find the handler
        std::map<const ResourceHandlerID, std::shared_ptr<IResourceHandler> >::const_iterator iter;
        iter = handlers_.find(handlerID);

        //Return a reference if handler found. Fatal error if not.
        assert((iter != handlers_.end()) && "ResourceManager::registerHandler() - Handler not registered!");
        return (iter->second);
      }


      /**
       * @brief getResourceHandler - Get a shared_pointer to the handler.
       * @return a shared_pointer to the resource handler.
       */
      template<class T> std::shared_ptr<TResourceHandler<T>> getResourceHandler() const
      {
        //Find the handler
        std::map<const ResourceHandlerID, std::shared_ptr<IResourceHandler> >::const_iterator iter;
        iter = handlers_.find(typeid(T).name());

        //Return a reference if handler found. Fatal error if not.
        assert((iter != handlers_.end()) && "ResourceManager::registerHandler() - Handler not registered!");
        return std::static_pointer_cast<TResourceHandler<T>>(iter->second);
      }

    private:
      std::map<const ResourceHandlerID, std::shared_ptr<IResourceHandler> > handlers_;


    };
  }
}
#endif
