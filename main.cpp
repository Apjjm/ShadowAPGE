#include "SFML_INCLUDES.hpp"
#include "APGE/APGE.hpp"

int main(int argc, char* argv[])
{  
  //Get Application
  APGE::Application& app = APGE::Application::getApplication();

  //Process the command line arguments
  if(!app.processArguments(argc,argv))
    return APGE::Application::ExitInvalidCommandLine;

  //Run the application
  app.run();

  return 0;
}

