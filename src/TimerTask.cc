#include  "TimerTask.h"
#include "TimeStamp.h"

using namespace flynet::net;


bool TimerTask::UpdateExpiration(uint64_t  ts){
    if(repeated_){
        expiration_ =  GetTimeStamp(interval_);
        return true;
    }
    return false;
}