#ifndef ISUBSCRIBER_HPP
#define ISUBSCRIBER_HPP
#include "APGE/Core/CoreTypes.hpp"

namespace APGE
{
  namespace Messaging
  {
    class ISubscriber
    {
    public:

      ISubscriber();

      virtual ~ISubscriber();

      virtual void recieveMessage(const IMessageArguments& message) = 0;

      void subscribeTo(IPublisher* publisher);
      void unsubscribeTo(IPublisher* publisher);

    private:
      std::vector<IPublisher*> publishers_;
    };
  }
}

#endif // ISUBSCRIBER_HPP
