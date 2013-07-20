#ifndef TRESOURCEHANDLER_HPP
#define TRESOURCEHANDLER_HPP
#include "APGE/Core/CoreTypes.hpp"
#include "IResourceFromMemoryData.hpp"
#include "IResourceFromStreamData.hpp"
#include "IResourceHandler.hpp"

namespace APGE
{
  namespace Resource
  {
    template<class T>
    /**
     * @brief The TResourceHandler class should be extended by a new class for each resource type one wishes to handle.
     * Each child class should pass a shared_ptr<T> to the dummy resource to use (E.g. error texture)
     * This class only maintains weak references to resources, so resources are freed when no longer in use.
     * To ensure resources persist through a level or the application lifetime, keep a list of loaded resources elsewhere (e.g. in level).
     */
    class TResourceHandler : public IResourceHandler
    {
    public:

      /**
       * @brief TResourceHandler
       * @param dummyResource dummy resource shared pointer (this dummy resource is encouraged to be defined as a static member in a subclass)
       */
      TResourceHandler(std::shared_ptr<T> dummyResource) : IResourceHandler(typeid(T).name()), dummyResource_(dummyResource)
      {
        LOGI("+TResourceHandler<"<<typeid(T).name()<<">");
      }

      /**
       * @brief ~TResourceHandler
       */
      virtual ~TResourceHandler()
      {
        LOGI("-TResourceHandler<"<<typeid(T).name()<<">");
      }

      /**
       * @brief getResourceFilename getter for file data of a given resource
       * @param resourceID
       * @return
       */
      virtual std::string getResourceFilename(const ResourceID resourceID) const
      {
        typename std::map<ResourceID, ResourceControlBlock>::const_iterator iter = resources_.find(resourceID);

        if(iter == resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::getResourceFilename("<<resourceID<<") - Invalid ID");
            return "";
          }
        return iter->second.fileName;
      }

      /**
       * @brief getResourceLoadMethod getter for load method of a given resource
       * @param resourceID
       * @return
       */
      virtual ResourceLoadMethod getResourceLoadMethod(const ResourceID resourceID) const
      {
        typename std::map<ResourceID, ResourceControlBlock>::const_iterator iter = resources_.find(resourceID);

        if(iter == resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::getResourceLoadMethod("<<resourceID<<") - Invalid ID");
            return ResourceLoadMethodUndefined;
          }
        return iter->second.loadMethod;
      }

      /**
       * @brief getResourceMemoryData getter for memory data of a given resource
       * @param resourceID
       * @return
       */
      virtual IResourceFromMemoryData getResourceMemoryData(const ResourceID resourceID) const
      {
        typename std::map<ResourceID, ResourceControlBlock>::const_iterator iter = resources_.find(resourceID);

        if(iter == resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::getResourceMemoryData("<<resourceID<<") - Invalid ID");
            return IResourceFromMemoryData();
          }
        return iter->second.memoryData;
      }

      /**
       * @brief getResourceStreamData getter for stream data of a given resource
       * @param resourceID
       * @return
       */
      virtual IResourceFromStreamData getResourceStreamData(const ResourceID resourceID) const
      {
        typename std::map<ResourceID, ResourceControlBlock>::const_iterator iter = resources_.find(resourceID);

        if(iter == resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::getResourceStreamData("<<resourceID<<") - Invalid ID");
            return IResourceFromStreamData();
          }
        return iter->second.streamData;
      }

      /**
       * @brief setResourceFilename Sets the resource loading mode to a file based approach with a given filename.
       * @param resourceID the resource id to use
       * @param filename the filename to load from
       */
      virtual void setResourceFilename(const ResourceID resourceID, std::string filename)
      {
        typename std::map<ResourceID, ResourceControlBlock>::iterator iter = resources_.find(resourceID);

        if(iter == resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::setResourceFilename("<<resourceID<<","<<filename<<") - Invalid ID");
            return;
          }
        iter->second.loadMethod = ResourceLoadMethodFile;
        iter->second.fileName = filename;
      }

      /**
       * @brief setResourceMemoryData Sets the loading mode to memory based with a given memory data object
       * @param resourceID
       * @param memoryData the memory data object to use, remember to use the correct subclass of IResourceFromMemoryData!
       */
      virtual void setResourceMemoryData(const ResourceID resourceID, IResourceFromMemoryData memoryData)
      {
        typename std::map<ResourceID, ResourceControlBlock>::iterator iter = resources_.find(resourceID);

        if(iter == resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::setResourceMemoryData("<<resourceID<<",<MEMDATA>) - Invalid ID");
            return;
          }
        iter->second.loadMethod = ResourceLoadMethodMemory;
        iter->second.memoryData = memoryData;
      }

      /**
       * @brief setResourceStreamData Sets the loading mode to stream based with a given stream data object
       * @param resourceID
       * @param streamData the stream data object to use, remember to use the correct subclass of IResourceFromStreamData!
       */
      virtual void setResourceStreamData(const ResourceID resourceID, IResourceFromStreamData streamData)
      {
        typename std::map<ResourceID, ResourceControlBlock>::iterator iter = resources_.find(resourceID);

        if(iter == resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::setResourceMemoryData("<<resourceID<<",<STREAMDATA>) - Invalid ID");
            return;
          }
        iter->second.loadMethod = ResourceLoadMethodStream;
        iter->second.streamData = streamData;
      }

      /**
       * @brief removeResource completely removes a resource from this handler. Note that the resource contents
       *will not be unloaded until the last resource shared_pointer gets destructed, however, no new shared pointers by
       *resource lookup using this class will be possible for the removed resource.
       * @param resourceID resource to remove
       */
      virtual void removeResource(const ResourceID resourceID)
      {
        typename std::map<ResourceID, ResourceControlBlock>::iterator iter = resources_.find(resourceID);

        if(iter == resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::removeResource("<<resourceID<<") - Invalid ID");
            return IResourceFromStreamData();
          }
        resources_.erase(iter++);
      }

      /**
       * @brief removeAllResources completely removes all resources from this handler. Note that resources will
       *not be unloaded until all shared pointer references are dropped. however, no new shared pointers by
       *resource lookup using this class will be possible.
       */
      virtual void removeAllResources()
      {
        typename std::map<ResourceID, ResourceControlBlock>::iterator iter = resources_.begin();

        while(iter != resources_.end())
          {
            resources_.erase(iter++);
          }
      }

      /**
       * @brief isLoaded Returns true if the resource is loaded
       * @param resourceID
       * @return
       */
      virtual bool isLoaded(const ResourceID resourceID) const
      {
        typename std::map<ResourceID, ResourceControlBlock>::const_iterator iter = resources_.find(resourceID);
        if(iter == resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::isLoaded("<<resourceID<<") - Invalid ID");
            return false;
          }
        return !(iter->second.resource.expired());
      }

      /**
       * @brief isResource Returns true if the resource id references a resource
       * @param resourceID
       * @return
       */
      virtual bool isResource(const ResourceID resourceID) const
      {
        typename std::map<ResourceID, ResourceControlBlock>::const_iterator iter = resources_.find(resourceID);
        return iter != resources_.end();
      }

      /**
       * @brief addResource Adds a resource with the given id as a from file resource.
       * @param resourceID
       * @param filename
       */
      void addResource(const ResourceID resourceID, std::string filename)
      {
        typename std::map<ResourceID, ResourceControlBlock>::iterator iter = resources_.find(resourceID);
        if(iter != resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::addResource("<<resourceID<<","<<filename<<") - ID Already is already in use!");
            return;
          }
        ResourceControlBlock rcb;
        rcb.resource();
        rcb.loadMethod = ResourceLoadMethodFile;
        rcb.fileName = filename;
        rcb.memoryData();
        rcb.streamData();
        resources_.insert(std::pair<ResourceID,ResourceControlBlock>(resourceID,rcb));
      }

      /**
       * @brief addResource Adds a resource with the given id as a from memory resource
       * @param resourceID
       * @param memory
       */
      void addResource(const ResourceID resourceID, IResourceFromMemoryData memory)
      {
        typename std::map<ResourceID, ResourceControlBlock>::iterator iter = resources_.find(resourceID);
        if(iter != resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::addResource("<<resourceID<<",<MEMDATA>) - ID Already is already in use!");
            return;
          }
        ResourceControlBlock rcb;
        rcb.resource();
        rcb.loadMethod = ResourceLoadMethodMemory;
        rcb.fileName = "";
        rcb.memoryData = memory;
        rcb.streamData();
        resources_.insert(std::pair<ResourceID,ResourceControlBlock>(resourceID,rcb));
      }

      /**
       * @brief addResource Adds a resource with the given id as a from stream resource
       * @param resourceID
       * @param stream
       */
      void addResource(const ResourceID resourceID, IResourceFromStreamData stream)
      {
        typename std::map<ResourceID, ResourceControlBlock>::iterator iter = resources_.find(resourceID);
        if(iter != resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::addResource("<<resourceID<<",<STREAMDATA>) - ID Already is already in use!");
            return;
          }
        ResourceControlBlock rcb;
        rcb.resource();
        rcb.loadMethod = ResourceLoadMethodStream;
        rcb.fileName = "";
        rcb.memoryData();
        rcb.streamData = stream;
        resources_.insert(std::pair<ResourceID,ResourceControlBlock>(resourceID,rcb));
      }

      /**
       * @brief addResource Adds a resource with the given id as a reference to another already loaded resource.
       * @param resourceID
       * @param resource
       */
      void addResource(const ResourceID resourceID, std::shared_ptr<T> resource)
      {
        typename std::map<ResourceID, ResourceControlBlock>::iterator iter = resources_.find(resourceID);
        if(iter != resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::addResource("<<resourceID<<",<RESOURCE>) - ID Already is already in use!");
            return;
          }
        ResourceControlBlock rcb;
        rcb.resource(resource);
        rcb.loadMethod = ResourceLoadMethodUndefined;
        rcb.fileName = "";
        rcb.memoryData();
        rcb.streamData();
        resources_.insert(std::pair<ResourceID,ResourceControlBlock>(resourceID,rcb));
      }

      /**
       * @brief getResource Gets a shared pointer to the given resource. If the resource is not loaded, load it.
       * @param resourceID
       * @return
       */
      std::shared_ptr<T> getResource(const ResourceID resourceID)
      {
        //Enforce unique resourceID
        typename std::map<ResourceID, ResourceControlBlock>::iterator iter = resources_.find(resourceID);
        if(iter != resources_.end())
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::getResource("<<resourceID<<") - ID is invalid");
            return dummyResource_;
          }

        //If Resource already loaded, return the pointer
        std::shared_ptr<T> ptrResource = iter->second.resource.lock();
        if(ptrResource)
          {
            return ptrResource;
          }

        //If Resource not loaded yet, construct an object for it & load it in.
        bool isLoaded = false;
        ptrResource = construct();
        if(ptrResource)
          {
            //Update weak reference
            iter->second.resource = ptrResource;

            //Attempt to load the resource if construction successful
            switch (iter->second.loadMethod)
              {
              case ResourceLoadMethodFile:
                isLoaded = loadResourceFromFile(*ptrResource,iter->second.fileName);
                break;
              case ResourceLoadMethodMemory:
                isLoaded = loadResourceFromMemory(*ptrResource,iter->second.memoryData);
                break;
              case ResourceLoadMethodStream:
                isLoaded = loadResourceFromStream(*ptrResource,iter->second.streamData);
                break;
              default:
                LOGE("TResourceHandler<"<<typeid(T).name()<<">::getResource("<<resourceID<<") - Undefined resource loading method");
                break;
              }
          }
        else
          {
            //Construction failed.
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::getResource("<<resourceID<<") - Unable to construct resource");
          }

        //If loading failed, return dummy resource, else return the resource.
        if(isLoaded)
          {
            return ptrResource;
          }
        else
          {
            LOGE("TResourceHandler<"<<typeid(T).name()<<">::getResource("<<resourceID<<") - Unable to load resource, falling back onto dummy resource.");
            return dummyResource_;
          }
      }

      /**
       * @brief isDummyResource determine if given resource is the dummy resource
       * @param resourcePointer
       * @return true if the dummy resource
       */
      inline bool isDummyResource(std::shared_ptr<T> resourcePointer)
      {
        return resourcePointer==dummyResource_;
      }

    protected:

      /**
       * @brief construct Perform construction (allocation through new and constructor call) for a given resource.
       * If you wish to specify a custom deleter, do it here in the shared pointer constructor.
       * It is suggested that the deleter method be a static member of the child subclass.
       * @return A shared pointer to a new resource. Returns shared_ptr<T>() if creation fails.
       */
      inline virtual std::shared_ptr<T> construct()
      {
        return std::shared_ptr<T>(new(std::nothrow) T);
      }

      /**
       * @brief loadResourceFromFile load a given resource from file
       * @param resource
       * @param filename
       * @return true if loading was sucessfull
       */
      virtual bool loadResourceFromFile(T& resource, std::string filename) = 0;

      /**
       * @brief loadResourceFromMemory load a given resource from memory
       * @param resource
       * @param memory
       * @return true if loading was sucessfull
       */
      virtual bool loadResourceFromMemory(T& resource, IResourceFromMemoryData memory) = 0;

      /**
       * @brief loadResourceFromStream load a given resource from a stream
       * @param resource
       * @param stream
       * @return true if loading was sucessfull
       */
      virtual bool loadResourceFromStream(T& resource, IResourceFromStreamData stream) = 0;

    private:

      struct ResourceControlBlock
      {
        std::weak_ptr<T> resource; //resource pointer
        ResourceLoadMethod loadMethod; //load method
        std::string fileName; //Filename for from file
        IResourceFromMemoryData memoryData; //for from memory
        IResourceFromStreamData streamData; //for from stream
      };
      std::map<ResourceID, ResourceControlBlock> resources_;
      std::shared_ptr<T> dummyResource_;

      //No noarg ctor.
      TResourceHandler();
    };
  }
}
#endif
