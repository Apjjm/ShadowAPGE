#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP
#include "APGE/Core/CoreTypes.hpp"
#include "SFML_INCLUDES.hpp"
#include "IComponent.hpp"

namespace APGE
{
  namespace Component
  {
    class SpriteComponent : public IComponent
    {

    public:
      SpriteComponent();

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

      inline void setCurrentFrameIndex(int frameIndex)
      {
        currentFrame_ = frameIndex;
      }

      inline unsigned int getCurrentFrameIndex() const
      {
        return currentFrame_;
      }

      inline void setFrameDelay(unsigned int frameDelay)
      {
        frameDelay_ = frameDelay;
      }

      inline float getFrameDelay() const
      {
        return frameDelay_;
      }

      inline void addFrame(std::shared_ptr<sf::Texture> frame)
      {
        frames_.push_back(frame);
        sprite_.setTexture(*frames_[currentFrame_]);
      }

      inline unsigned int getFrameCount() const
      {
        return frames_.size();
      }

      inline void clearFrames()
      {
        frames_.clear();
      }

      inline void removeFrame(unsigned int frameIndex)
      {
        assert(frameIndex < frames_.size() && "SpriteComponent::removeFrame[] - Frame index OOB.");
        frames_.erase(frames_.begin() + frameIndex);
        currentFrame_ = currentFrame_ % frames_.size();
        if(frames_.size() > 0 )
          {
            sprite_.setTexture(*frames_[currentFrame_]);
          }
      }

      inline std::shared_ptr<sf::Texture> getFrame(unsigned int frameIndex) const
      {
        assert(frameIndex < frames_.size() && "SpriteComponent::getFrame() - Frame index OOB.");
        return frames_[frameIndex];
      }

      inline std::shared_ptr<sf::Texture> operator[](unsigned int frameIndex) const
      {
        assert(frameIndex < frames_.size() && "SpriteComponent::operator[] - Frame index OOB.");
        return frames_[frameIndex];
      }

      inline std::shared_ptr<sf::Texture> getCurrentFrame() const
      {
        return frames_[currentFrame_];
      }

      inline sf::Sprite& getSprite()
      {
        return sprite_;
      }

     private:

      float currentFrameTime_;
      float frameDelay_;
      unsigned int currentFrame_;
      std::vector<std::shared_ptr<sf::Texture>> frames_;
      sf::Sprite sprite_;
      std::string spriteFile;
    };
  }
}

#endif // SPRITECOMPONENT_HPP
