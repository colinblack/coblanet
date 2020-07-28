#ifndef     _TIME_STAMP_H_
#define     _TIME_STAMP_H_

#include <stdint.h>
#include <sys/time.h>
#include <errno.h>

namespace flynet{
    const  uint32_t  microSecPerSec = 1000000;

    uint64_t  GetTimeStampNow();
    uint64_t GetTimeStamp(double );
}



#endif