#include "SFML_INCLUDES.hpp"
#include "APGE/APGE.hpp"

int main(int argc, char* argv[])
{  
  //Get Application
  APGE::Application& app = APGE::Application::getApplication();

  //Process the command line arguments
  if(!app.processArguments(argc,argv))
    return APGE::Application::ExitInvalidCommandLine;


  sf::Window window(sf::VideoMode(800, 600), "Test");

  // run the program as long as the window is open
  while (window.isOpen())
  {
      // check all the window's events that were triggered since the last iteration of the loop
      sf::Event event;
      while (window.pollEvent(event))
      {
          // "close requested" event: we close the window
          if (event.type == sf::Event::Closed)
              window.close();
      }
  }

  return 0;
}

