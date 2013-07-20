#ifndef IRESOURCEHANDLER_HPP
#define IRESOURCEHANDLER_HPP
#include "APGE/Core/CoreTypes.hpp"
#include "IResourceFromMemoryData.hpp"
#include "IResourceFromStreamData.hpp"

namespace APGE
{
  namespace Resource
  {
    /**
     * @brief The IResourceHandler class is an untemplated interface for a resource handler.
     * When implementing resource handlers please extend TResourceHandler!
     */
    class IResourceHandler : sf::NonCopyable
    {
    public:

      /**
       * @brief IResourceHandler Construct resource handler with given id. This ID should be unique!
       * @param handlerID
       */
      IResourceHandler(const ResourceHandlerID handlerID) : handlerID_(handlerID)
      {
      }

      /**
       * @brief ~IResourceHandler
       */
      virtual ~IResourceHandler()
      {
      }

      /**
       * @brief getHandlerID getter for handler id as specified in ctor.
       * @return
       */
      inline ResourceHandlerID getHandlerID()
      {
        return handlerID_;
      }

      /**
       * @brief getResourceFilename getter for file data of a given resource
       * @param resourceID
       * @return
       */
      virtual std::string getResourceFilename(const ResourceID resourceID) const = 0;

      /**
       * @brief getResourceLoadMethod getter for load method of a given resource
       * @param resourceID
       * @return
       */
      virtual ResourceLoadMethod getResourceLoadMethod(const ResourceID resourceID) const = 0;

      /**
       * @brief getResourceMemoryData getter for memory data of a given resource
       * @param resourceID
       * @return
       */
      virtual IResourceFromMemoryData getResourceMemoryData(const ResourceID resourceID) const = 0;

      /**
       * @brief getResourceStreamData getter for stream data of a given resource
       * @param resourceID
       * @return
       */
      virtual IResourceFromStreamData getResourceStreamData(const ResourceID resourceID) const = 0;

      /**
       * @brief setResourceFilename Sets the resource loading mode to a file based approach with a given filename.
       * @param resourceID the resource id to use
       * @param filename the filename to load from
       */
      virtual void setResourceFilename(const ResourceID resourceID, std::string filename) = 0;

      /**
       * @brief setResourceMemoryData Sets the loading mode to memory based with a given memory data object
       * @param resourceID
       * @param memoryData the memory data object to use, remember to use the correct subclass of IResourceFromMemoryData!
       */
      virtual void setResourceMemoryData(const ResourceID resourceID, IResourceFromMemoryData memoryData) = 0;

      /**
       * @brief setResourceStreamData Sets the loading mode to stream based with a given stream data object
       * @param resourceID
       * @param streamData the stream data object to use, remember to use the correct subclass of IResourceFromStreamData!
       */
      virtual void setResourceStreamData(const ResourceID resourceID, IResourceFromStreamData streamData)  = 0;

      /**
       * @brief removeResource completely removes a resource from this handler. Note that the resource contents
       *will not be unloaded until the last resource shared_pointer gets destructed, however, no new shared pointers by
       *resource lookup using this class will be possible for the removed resource.
       * @param resourceID resource to remove
       */
      virtual void removeResource(const ResourceID resourceID) = 0;

      /**
       * @brief removeAllResources completely removes all resources from this handler. Note that resources will
       *not be unloaded until all shared pointer references are dropped. however, no new shared pointers by
       *resource lookup using this class will be possible.
       */
      virtual void removeAllResources() = 0;

      /**
       * @brief isLoaded Returns true if the resource is loaded
       * @param resourceID
       * @return
       */
      virtual bool isLoaded(const ResourceID resourceID) const = 0;

      /**
       * @brief isResource Returns true if the resource id references a resource
       * @param resourceID
       * @return
       */
      virtual bool isResource(const ResourceID resourceID) const = 0;
    private:
      ResourceHandlerID handlerID_;

      IResourceHandler();
    };

  }
}
#endif
