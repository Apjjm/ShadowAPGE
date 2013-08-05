#include "TextureResourceHandler.hpp"
#include "Boost/filesystem.hpp"

namespace APGE
{
  namespace Resource
  {

    //Static Members
    std::shared_ptr<sf::Texture> TextureResourceHandler::dummyTexture_(
        new(std::nothrow) sf::Texture);

    //Functions
    TextureResourceHandler::TextureResourceHandler()
      : TResourceHandler<sf::Texture>(dummyTexture_)
    {
    }

    bool TextureResourceHandler::loadResourceFromFile(sf::Texture& resource, std::string filename)
    {
      bool result = false;
      //Check file exists
      if(boost::filesystem::exists(filename))
        {
          result = resource.loadFromFile(filename);
        }
      else
        {
          LOGE("TextureResourceHandler::loadResourceFromFile() - File not found: "<<filename);
        }
      return result;
    }
  }
}
