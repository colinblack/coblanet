#ifndef   _TIMERTASK_H_
#define  _TIMERTASK_H_

#include "CallBacks.h"

namespace  flynet {
namespace  net{
class TimerTask{
public:
        TimerTask(uint64_t  ts,  double interval,   TimerTaskCallBack cb)
                : expiration_(ts)
                ,  interval_(interval)
                ,   repeated_(interval > 0.0)
                ,  callback_(std::move(cb)){
        }
        void Run(){
                callback_();
        }

        uint64_t Expiration(){
                return expiration_;
        }

        double Interval(){
                return interval_;
        }

        bool Repeated(){
                return repeated_;
        } 


       bool UpdateExpiration(uint64_t ts);
private:
        uint64_t  expiration_;
        double  interval_;
        bool        repeated_; 
        TimerTaskCallBack   callback_;
};

}

}

#endif   /*_TIMERTASK_H_  */