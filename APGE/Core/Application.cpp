#include "Application.hpp"

namespace APGE
{
  std::unique_ptr<Application> Application::application_ = std::unique_ptr<Application>();

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
    running_ = true;
    /* TODO */
    running_ = false;
    return Application::ExitSuccess;
  }

}

