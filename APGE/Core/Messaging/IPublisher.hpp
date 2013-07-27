#ifndef IPUBLISHER_HPP
#define IPUBLISHER_HPP
#include "APGE/Core/CoreTypes.hpp"

namespace APGE
{
  namespace Messaging
  {
    class IPublisher
    {
    public:

      IPublisher();

      virtual ~IPublisher();

      inline void setNotifyEnabled(bool enabled)
      {
        if(subscribeEnabled_) notifyEnabled_ = enabled;
      }

      inline bool getNotifyEnabled()
      {
        return notifyEnabled_;
      }

      void notify(const IMessageArguments& message);

    private:
      friend class ISubscriber;
      void subscribe(ISubscriber* sub);
      void unsubscribe(ISubscriber* sub);

      std::vector<ISubscriber*> subscribers_;
      bool notifyEnabled_;
      bool subscribeEnabled_;
    };
  }
}
#endif // IPUBLISHER_HPP
