#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "CoreTypes.hpp"

namespace APGE
{

  /**
  * @brief The Application class is a singleton which controls the windowing and events.
*/
  class Application : sf::NonCopyable
  {

  public:

    ~Application();

    /**
     * @brief The ExitCode enum
     */
    enum ExitCode
    {
      ExitSuccess = EXIT_SUCCESS,   //no errors
      ExitImmidiate = EXIT_FAILURE, //flat exit call
      ExitGeneralErrorAndFree = 2,  //Exit but try to free resources
      ExitResourceErrorAndFree = 3, //Exit but try to free resources
      ExitGraphicsErrorAndFree = 4, //Exit but try to free resources
      ExitInvalidCommandLine = 5    //Exit but try to free resources
    };

    /**
   * @brief Application::getApplication - getter for singleton application
   * @return the singleton application reference
   */
    static Application& getApplication();

    /**
   * @brief processArguments Process any commandline arguments
   * @param argc
   * @param argv
   * @return true if run can be called. Exit with invalidcommandline if false!
   */
    bool processArguments(int argc, char* argv[]);

    /**
   * @brief run the application. Process arguments before doing this!
   * @return the exit code of the application.
   */
    ExitCode run();

    /**
   * @brief stop stop with specified exit code
   * @param exitCode defaults to immidiate exit
   */
    void stop(ExitCode exitCode = Application::ExitImmidiate);

    /**
   * @brief isRunning
   * @return True only if application is running
   */
    inline bool isRunning() const
    {
      return running_;
    }

  private:
    static std::unique_ptr<Application> application_;
    bool running_;
    std::string directory_;

    Application();
  };
}
#endif // APPLICATION_HPP
