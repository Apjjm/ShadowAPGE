#include "SpriteComponent.hpp"
#include "APGE/Core/Resource/TextureResourceHandler.hpp"

namespace APGE
{
  namespace Component
  {
    SpriteComponent::SpriteComponent()
      : IComponent(typeid(SpriteComponent).name()),
      currentFrameTime_(0),
      frameDelay_(1),
      currentFrame_(0)
    {
    }

    void SpriteComponent::update(float timestep)
    {
      if(getFrameCount() > 0)
        {
          //Step forwards through frames based on timestep & delay
          currentFrameTime_ += timestep;
          while(currentFrameTime_ > frameDelay_)
            {
              currentFrame_++;
              currentFrameTime_ -= frameDelay_;
            }

          //Loop frame index
          currentFrame_ = currentFrame_ % getFrameCount();

          //Configure sprite such that it shows the current frame
          sprite_.setTexture(*frames_[currentFrame_],true);
        }
    }

    std::string SpriteComponent::toString() const
    {
      LOGE("SpriteComponent::fromString() not implemented.");
      return "";
    }

    void SpriteComponent::fromString(const std::string& input)
    {
      spriteFile = input;
      LOGE("SpriteComponent::fromString() not implemented.");
      /* todo */
    }
  }
}
