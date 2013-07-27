#include "Application.hpp"
#include "APGE/Core/Resource/IResourceHandler.hpp"
#include "APGE/Core/Resource/TResourceHandler.hpp"
#include "APGE/Core/Resource/TextureResourceHandler.hpp"
#include "APGE/Core/Entity/Entity.hpp"
#include "APGE/Core/Component/PositionComponent.hpp"
#include "APGE/Core/Component/SpriteComponent.hpp"

namespace APGE
{
  std::unique_ptr<Application> Application::application_(nullptr);

  Application& Application::getApplication()
  {

    if(!application_)
      {
        application_.reset(new Application());
        assert(application_ && "Could not instantiate application.");
      }
    return *(application_);
  }

  Application::Application()
  {
    LOGI("=====Application Start=====");
    running_ = false;
  }

  Application::~Application()
  {
    LOGI("=====Application End=====");
    /* TODO Log Memory */
  }

  bool Application::processArguments(int argc, char *argv[])
  {
    LOGI("---PROCESSING ARGUMENTS---");
    for(int i =0; i<argc; ++i)
      {
        std::string argument(argv[i]);
        LOGI(argument);

        if(i==0)
          {
            //Find out exection directory
            boost::filesystem::path programPath(argument);
            directory_ = programPath.parent_path().string();
          }
        else
          {
            /* TODO */
          }

      }

    return true;
  }

  void Application::stop(Application::ExitCode exitCode)
  {

    switch(exitCode)
      {
      case Application::ExitImmidiate:
        LOGI("---STOPPING IMMIDIATE---");
        exit(exitCode);
        break;
      default:
        LOGI("---STOPPING---");
        running_ = false;
        break;
      }
  }

  Application::ExitCode Application::run()
  {
    //Initilisation
    if(!configureResourceManager())
      return Application::ExitResourceError;

    LOGI("---START MAIN LOOP---");
    testRoutine();
    LOGI("---END MAIN LOOP---");
    //Release the resource manager before exit
    resourceManager_.reset();
    return Application::ExitSuccess;
  }

  bool Application::configureResourceManager()
  {
    LOGI("---CREATING RESOURCE HANDLERS---");
    using namespace Resource;

    //Create Resource Manager
    resourceManager_ = std::shared_ptr<ResourceManager>(
                          new(std::nothrow)ResourceManager );
    if(!resourceManager_)
      {
        LOGE("Application::configureResourceManager() could not create resource manager.");
        return false;
      }

    //Add handlers
    bool result = true;
    result &= resourceManager_->registerHandler(std::shared_ptr<IResourceHandler>(
                                                new(std::nothrow)TextureResourceHandler));

    return result;
  }

  void Application::testRoutine()
  {
    //Config component mgr
    componentManager_ = std::shared_ptr<Resource::ResourceManager>
        (new(std::nothrow)Resource::ResourceManager());

    Component::TComponentHandler<Component::PositionComponent>* t =
        (new(std::nothrow) Component::TComponentHandler<Component::PositionComponent>);

    componentManager_->registerHandler(std::shared_ptr<Component::TComponentHandler<Component::PositionComponent>>(t));

    componentManager_->registerHandler(std::shared_ptr<Component::TComponentHandler<Component::SpriteComponent>>
                                       (new(std::nothrow) Component::TComponentHandler<Component::SpriteComponent>));
    running_ = true;

    //Add a temp test resource
    std::shared_ptr<Resource::TResourceHandler<sf::Texture>> texHandler;
    texHandler = getResourceManager()->getResourceHandler<sf::Texture>();
    texHandler->addResource("TEST",directory_ + "/testImage.png");

    //Create a test entity
    Entity::Entity ent("TestEntity");
    ent.addComponent<Component::PositionComponent>();
    ent.addComponent<Component::SpriteComponent>();

    //Configure Components
    ent.getComponent<Component::SpriteComponent>()->addFrame(texHandler->getResource("TEST"));
    ent.getComponent<Component::PositionComponent>()->setPosition(sf::Vector2f(10,10));

    //Create Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ent.getComponent<Component::SpriteComponent>()->update(0.1f);
        window.clear();
        window.draw(ent.getComponent<Component::SpriteComponent>()->getSprite());
        window.display();
        sf::sleep(sf::microseconds(16666));
    }

    running_ = false;
  }
}

