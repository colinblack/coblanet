#ifndef  _TIMER_H_
#define  _TIMER_H_

#include <cstdint>
#include <utility>
#include <vector>
#include <set>
#include "Channel.h"
#include "TimerTask.h"

namespace flynet{
namespace net{

class EventLoop;

class Timer{
public:
        Timer(EventLoop* loop);
        ~Timer();
        TimerEv  AddTimer(TimerTaskCallBack cb ,  double after,  double  interval);

private:
        using  Entry=std::pair<uint64_t,  TimerTask*>;
        using  TimeStamp=uint64_t;
        using   TimerTasks=std::set<Entry>;

        void HandleRead();
        std::vector<Entry>  GetExpired(TimeStamp  now);
        void Rest(std::vector<Entry>& ,  TimeStamp );
        void  RestTimer(uint64_t );
        void ReadTimerfd(); //epoll水平触发必须冲fd中读出数据,  否则会一直触发　

private:
    uint32_t timerfd_; 
    Channel  timerChannel_;
    TimerTasks  timerTasks_;
};

}

}

#endif  /* _TIMER_H_ */