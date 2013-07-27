#include "IComponent.hpp"
#include "APGE/Core/Entity/Entity.hpp"

namespace APGE
{
  namespace Component
  {
    void IComponent::setEntity(Entity::Entity* entity)
    {
      assert(entity_ == nullptr && "IComponent::setEntity() called when entity already set");
      entity_ = entity;
    }

    Entity::Entity* IComponent::getEntity() const
    {
      assert(entity_ != nullptr && "IComponent::getEntity() called before entity pointer set");
      return entity_;
    }

    IComponent::IComponent(ComponentType componentType) :
      componentType_(componentType),
      entity_(nullptr)
    {
      LOGD("    IComponent::ctor");
    }

    IComponent::~IComponent()
    {
      LOGD("    IComponent::Dtor");
    }
  }
}
