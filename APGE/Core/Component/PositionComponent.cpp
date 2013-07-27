#include "PositionComponent.hpp"

namespace APGE
{
  namespace Component
  {
    PositionComponent::PositionComponent()
      : IComponent(typeid(PositionComponent).name())
    {

    }

    void PositionComponent::update(float timestep)
    {
      /* Do Nothing */
    }

    std::string PositionComponent::toString() const
    {
      return "(" + std::to_string(position_.x) + "," + std::to_string(position_.y) + ")";
    }

    void PositionComponent::fromString(const std::string& input)
    {
      LOGE("PositionComponent::fromString() not implemented.");
      /* todo */
    }
  }
}
