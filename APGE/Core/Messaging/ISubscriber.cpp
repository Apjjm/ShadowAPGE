#include "ISubscriber.hpp"
#include "IPublisher.hpp"

namespace APGE
{
  namespace Messaging
  {
    ISubscriber::ISubscriber()
    {

    }

    ISubscriber::~ISubscriber()
    {
      std::vector<IPublisher*>::iterator iter = publishers_.begin();
      while(iter != publishers_.end())
        {
          (*iter)->unsubscribe(this);
          publishers_.erase(iter++);
        }
    }

    void ISubscriber::subscribeTo(IPublisher *publisher)
    {
      publisher->subscribe(this);
      publishers_.push_back(publisher);
    }

    void ISubscriber::unsubscribeTo(IPublisher *publisher)
    {
      std::vector<IPublisher*>::iterator iter = publishers_.begin();
      while(iter != publishers_.end())
        {
          if(*iter == publisher)
            {
              publisher->unsubscribe(this);
              publishers_.erase(iter++);
              return;
            }
        }
    }
  }
}
