#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP
#include "APGE/Core/CoreTypes.hpp"

namespace APGE
{  
  namespace Component
  {
    class IComponent : boost::noncopyable
    {
    public:
      /**
       * @brief IComponent constructor
       * @param componentType a unique identitifier for each child class
       * @param entity pointer to hosting entity
       */
      IComponent(ComponentType componentType);

      /**
       * @brief ~IComponent
       */
      virtual ~IComponent();

      /**
       * @brief update
       * @param timestep
       */
      virtual void update(float timestep) = 0;

      /**
       * @brief toString convert the component to a string representation
       */
      virtual std::string toString() const = 0;

      /**
       * @brief fromString initialise the component from a string representation
       */
      virtual void fromString(const std::string& input) = 0;

      /**
       * @brief getComponentType
       * @return
       */
      inline ComponentType getComponentType() const
      {
        return componentType_;
      }

      void setEntity(Entity::Entity* entity);

      Entity::Entity* getEntity() const;

    private:
      ComponentType componentType_;
      Entity::Entity* entity_;
    };
  }
}



#endif // ICOMPONENT_HPP
