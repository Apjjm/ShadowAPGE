#include "Entity.hpp"
#include "APGE/Core/Application.hpp"

namespace APGE
{
  namespace Entity
  {
    Entity::Entity(EntityID id) :
      entityID_(id),
      componentManager_(APGE::Application::getApplication().getComponentManager())
    {
      LOGD("+Entity("<<id<<")");
    }

    Entity::~Entity()
    {
      LOGD("-Entity("<<entityID_<<")");
    }

  }
}
