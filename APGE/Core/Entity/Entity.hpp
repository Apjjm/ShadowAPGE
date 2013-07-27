#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "APGE/Core/CoreTypes.hpp"
#include "APGE/Core/Component/IComponent.hpp"
#include "APGE/Core/Resource/ResourceManager.hpp"
#include "APGE/Core/Component/TComponentHandler.hpp"


namespace APGE
{
  namespace Entity
  {
    class Entity : sf::NonCopyable
    {
    public:
      Entity(EntityID id);

      ~Entity();

      template<class T> void addComponent()
      {
        LOGD("Entity("<<entityID_<<")::addComponent<"<<typeid(T).name()<<">() called");
        //Aqcuire the handler for this component type
        std::shared_ptr<Component::TComponentHandler<T>> handler =
            std::static_pointer_cast<Component::TComponentHandler<T>>(componentManager_->getResourceHandler<T>());

        //Generate ID for the component to tie it to this entity
        Resource::ResourceID entityComponentID = entityID_;
        entityComponentID.append("_").append(typeid(T).name());

        //Register & get component through handler
        if(!handler->isResource(entityComponentID))
         {
           handler->addResource(entityComponentID);
         }
        std::shared_ptr<Component::IComponent> component =
            std::static_pointer_cast<Component::IComponent>(handler->getResource(entityComponentID));

        //Add component to the entity component mapping
        components_.insert(std::pair<std::size_t,std::shared_ptr<Component::IComponent>>(
                             typeid(T).hash_code(),
                             component));

        //Add reference to self into component
        component->setEntity(this);
      }

      template<class T> std::shared_ptr<T> getComponent() const
      {
        typename std::map<std::size_t,std::shared_ptr<Component::IComponent>>::const_iterator iter;
        iter = components_.find(typeid(T).hash_code());

        if(iter == components_.end())
          {
            LOGE("Entity::getComponent<"<<typeid(T).name()<<">() - Unable to obtain component.");
            return std::shared_ptr<T>();
          }
        else
          {
            return std::static_pointer_cast<T>(iter->second);
          }
      }

      template<class T> inline bool hasComponent() const
      {
        return components_.find(typeid(T).hash_code()) == components_.end();
      }

      inline EntityID getEntityID()
      {
        return entityID_;
      }

    private:
      EntityID entityID_;
      std::shared_ptr<Resource::ResourceManager> componentManager_;
      std::map<std::size_t,std::shared_ptr<Component::IComponent>> components_;

    };
  }
}


#endif // ENTITY_HPP
