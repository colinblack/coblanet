#include  "TimeStamp.h"
#include  "Logger.h"

using namespace flynet;

uint64_t  flynet::GetTimeStampNow(){
    timeval  tv;
    uint64_t  timestamp ;
    int ret  =  ::gettimeofday(&tv, nullptr);
        if(ret == EFAULT ||  ret == EINVAL || ret == EPERM){
            timestamp = ret;
        }else{
            timestamp = tv.tv_sec * microSecPerSec + tv.tv_usec;
        }
        
        return timestamp;
}

uint64_t  flynet::GetTimeStamp(double sec){
    uint64_t ts = GetTimeStampNow();
    if(ts == EFAULT ||  ts == EINVAL ||  ts  == EPERM)
        return  ts;

    return  ts + sec * microSecPerSec;
}