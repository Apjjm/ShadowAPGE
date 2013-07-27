#ifndef POSITIONCOMPONENT_HPP
#define POSITIONCOMPONENT_HPP
#include "APGE/Core/CoreTypes.hpp"
#include "IComponent.hpp"

namespace APGE
{
  namespace Component
  {
    class PositionComponent : public IComponent
    {
    public:
      PositionComponent();

      /**
       * @brief update
       * @param timestep
       */
      virtual void update(float timestep);

      /**
       * @brief toString convert the component to a string representation
       */
      virtual std::string toString() const;

      /**
       * @brief fromString initialise the component from a string representation
       */
      virtual void fromString(const std::string& input);

      /**
       * @brief setPosition
       * @param position
       */
      inline void setPosition(sf::Vector2f position)
      {
        position_ = position;
      }

      /**
       * @brief getPosition
       * @return
       */
      inline sf::Vector2f getPosition() const
      {
        return position_;
      }

     private:
      sf::Vector2f position_;
    };
  }
}
#endif // POSITIONCOMPONENT_HPP
