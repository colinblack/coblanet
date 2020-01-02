#include <vector>
#include <sys/epoll.h>
#include "Channel.h"

class EventLoop{
public:
   EventLoop();
   ~EventLoop(){}
public:
   void loop();
   void AddChannel(Channel* channel);


private:
   int32_t epollFd_;
   std::vector<epoll_event> eventData_;
};
