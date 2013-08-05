#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "CoreTypes.hpp"
#include "boost/filesystem.hpp"
#include "SFML_INCLUDES.hpp"
#include "Resource/TResourceHandler.hpp"
#include "Resource/ResourceManager.hpp"


namespace APGE
{

  /**
  * @brief The Application class is a singleton.
  * Application controls the windowing and events.
*/
  class Application : boost::noncopyable
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
      ExitResourceError = 3,
      ExitGraphicsError = 4,
      ExitInvalidCommandLine = 5
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

    /**
     * @brief getResourceManager
     * @return shared pointer to resource manager
     */
    inline std::shared_ptr<Resource::ResourceManager> getResourceManager() const
    {
      return resourceManager_;
    }

    inline std::shared_ptr<Resource::ResourceManager> getComponentManager() const
    {
      return componentManager_;
    }
   protected:

    /**
     * @brief configureResourceManager - Called by run ONCE to initilise the resource manager.
     * @return true if resource manager was configured successfully
     */
    bool configureResourceManager();


   private:
    static std::unique_ptr<Application> application_;

    bool running_;
    std::string directory_;
    std::shared_ptr<Resource::ResourceManager> resourceManager_;
    std::shared_ptr<Resource::ResourceManager> componentManager_;


    void testRoutine();

    /**
     * @brief Application - Hidden constructor for singleton pattern.
     */
    Application();
  };
}
#endif // APPLICATION_HPP
