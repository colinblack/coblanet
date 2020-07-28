#ifndef _EVENTLOOP_H_
#define _EVENTLOOP_H_

#include <vector>
#include <sys/epoll.h>
#include  "Timer.h"
//#include "Channel.h"


namespace flynet{
namespace net{

class Channel;

class EventLoop{
public:
   EventLoop();
   ~EventLoop(){}
public:
   void loop();
   void AddChannel(Channel* channel);
//   TimerEv  TimerStart(TimerTaskCallBack  cb,    uint64_t  after, uint64_t  repeat );

private:
   static const int32_t epollInitVaule = 16;
   int32_t epollFd_;
   std::vector<epoll_event> eventData_;
};

}
} 




#endif  /*_EVENTLOOP_H_*/