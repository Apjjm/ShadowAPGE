#ifndef TEXTURERESOURCEHANDLER_HPP
#define TEXTURERESOURCEHANDLER_HPP
#include "APGE/Core/CoreTypes.hpp"
#include "TResourceHandler.hpp"

namespace APGE
{
  namespace Resource
  {
    class TextureResourceHandler : public TResourceHandler<sf::Texture>
    {
    public:
      TextureResourceHandler();

    protected:

      /**
       * @brief loadResourceFromFile load a given resource from file
       * @param resource
       * @param filename
       * @return true if loading was sucessfull
       */
      virtual bool loadResourceFromFile(sf::Texture& resource, std::string filename);

      //TODO: virtual bool loadResourceFromMemory(sf::Texture& resource, IResourceFromMemoryData memory);
      //TODO: virtual bool loadResourceFromStream(sf::Texture& resource, IResourceFromStreamData stream);

    private:
      static std::shared_ptr<sf::Texture> dummyTexture_;

    };
  }
}
#endif // TEXTURERESOURCEHANDLER_HPP
