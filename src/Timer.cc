#include  "Timer.h"
#include  "Logger.h"
#include  "TimerTask.h"
#include  "TimeStamp.h"
#include   <cerrno>
#include   <cstring>
#include   <sys/timerfd.h>
#include   <set>
#include  <iterator>
#include <unistd.h>

namespace flynet{
    namespace net{

    int32_t  CreateTimerfd(){
            int32_t timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
            if(-1 == timerfd){
                LOG_ERROR("timerfd create error: %s \n", strerror(errno));
                exit(-1);
            }

            return timerfd;
    }
    }
}

using namespace flynet;
using namespace flynet::net;

Timer::Timer(EventLoop* loop)
        : timerfd_(CreateTimerfd())
        , timerChannel_(loop, timerfd_){

        timerChannel_.EnableReading();
        timerChannel_.SetReadCallBack(std::bind(&Timer::HandleRead,  this));
}

Timer::~Timer(){

}

void Timer::HandleRead(){
    ReadTimerfd();
    TimeStamp now = GetTimeStampNow();
    std::vector<Timer::Entry>  expired =  GetExpired(now);
    
    for(auto & v : expired){
        v.second->Run();            
    }
    Rest(expired, now);  //处理重复定时　　
}

std::vector<Timer::Entry>  Timer::GetExpired(TimeStamp  now){
    auto begin = timerTasks_.begin();
    auto end =  timerTasks_.lower_bound(Entry(now,  reinterpret_cast<TimerTask*>(UINTPTR_MAX)));
    std::vector<Timer::Entry>  expirse ;

    int dis = std::distance(begin, end);
    expirse.reserve(dis);

    std::copy(begin, end, std::back_inserter(expirse)); 
    timerTasks_.erase(begin, end);

    return expirse;
}

TimerEv  Timer::AddTimer(TimerTaskCallBack cb ,  double after,  double  interval){
    uint64_t  ts  =  GetTimeStamp(after); 
    if (ts == EFAULT ||  ts == EINVAL ||  ts  == EPERM){
       return nullptr;
    }
    bool earlierChange = false;
    if(timerTasks_.begin() ==  timerTasks_.end() || ts < timerTasks_.begin()->first ){
        earlierChange = true;
    }

    TimerTask*  task  =  new TimerTask(ts, interval, std::move(cb));
    timerTasks_.insert(Entry(ts,  task));

    if(earlierChange){
        RestTimer(ts);
    }

    return  task;
}

void Timer::Rest(std::vector<Entry>& expired,  TimeStamp now){
    for(auto&  v : expired){
        if(v.second->Repeated()){
            v.second->UpdateExpiration(GetTimeStamp(v.second->Interval()));
            timerTasks_ .insert(Entry(v.second->Expiration(), v.second));
        }else{
            delete v.second;
        }

        uint64_t nextExpire = 0;
        if(!timerTasks_.empty()){
            nextExpire =  timerTasks_.begin()->second->Expiration();
        }
        if(nextExpire !=0)
            RestTimer(nextExpire);
    }

}

void Timer::RestTimer(uint64_t timestamp){
    uint64_t  ts =  timestamp - GetTimeStampNow();
    LOG_DEBUG("time:  %ld \n", ts);
    if(ts < 100){
        ts = 100;
    }

    itimerspec   newVaule;
    newVaule.it_value.tv_sec = ts /  microSecPerSec;
    newVaule.it_value.tv_nsec = (ts % microSecPerSec) * 1000;

    int ret = ::timerfd_settime(timerfd_,  CLOCK_REALTIME, &newVaule, nullptr);
    if(ret < 0){
        LOG_ERROR("set timer err:  %s \n", strerror(errno));
    }
}


void  Timer::ReadTimerfd(){
  uint64_t howmany;
  ssize_t n = ::read(timerfd_, &howmany, sizeof howmany);
  if(n != sizeof howmany){
      LOG_ERROR("timer error, n=%d, howmany=%d \n", n, howmany);
  }
}
