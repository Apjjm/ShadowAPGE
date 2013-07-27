#include "ISubscriber.hpp"
#include "IPublisher.hpp"

namespace APGE
{
  namespace Messaging
  {
    IPublisher::IPublisher() :
      notifyEnabled_(true),
      subscribeEnabled_(true)
    {
    }

    IPublisher::~IPublisher()
    {
      subscribeEnabled_ = false;
      notifyEnabled_ = false;

      std::vector<ISubscriber*>::iterator iter = subscribers_.begin();

      while(iter != subscribers_.end())
        {
          (*iter)->unsubscribeTo(this);
          subscribers_.erase(iter++);
        }

    }

    void IPublisher::subscribe(ISubscriber *sub)
    {
      subscribers_.push_back(sub);
    }

    void IPublisher::unsubscribe(ISubscriber *sub)
    {
      std::vector<ISubscriber*>::iterator iter = subscribers_.begin();
      while(iter != subscribers_.end())
        {
          if(*iter == sub)
            {
              subscribers_.erase(iter++);
              return;
            }
        }
    }

    void IPublisher::notify(const IMessageArguments& message)
    {
      std::vector<ISubscriber*>::iterator iter = subscribers_.begin();

      while(iter != subscribers_.end())
        {
          (*iter)->recieveMessage(message);
          iter++;
        }
    }
  }
}
