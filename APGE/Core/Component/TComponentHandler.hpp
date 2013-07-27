#ifndef TCOMPONENTHANDLER_HPP
#define TCOMPONENTHANDLER_HPP
#include "APGE/Core/CoreTypes.hpp"
#include "APGE/Core/Resource/TResourceHandler.hpp"
#include "IComponent.hpp"

using namespace APGE::Resource;

namespace APGE
{
  namespace Component
  {

    template<class T> class TComponentHandler : public TResourceHandler<T>
    {
    public:
      TComponentHandler()
        : TResourceHandler<T>(dummyComponent_)
      {

      }


    protected:

      /* TODO Overrides of loading methods */

    private:
      static std::shared_ptr<T> dummyComponent_;

    };

    //Init static member
    template<class T> std::shared_ptr<T> TComponentHandler<T>::dummyComponent_(new(std::nothrow) T());
  }
}

#endif // TCOMPONENTHANDLER_HPP
