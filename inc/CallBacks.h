#ifndef _CALL_BACKS_H_
#define _CALL_BACKS_H_

#include  <functional>

namespace flynet{
    namespace net{
            class TimerTask;

            using  TimerTaskCallBack  = std::function<void()>;
            using  MessageCallback = std::function<bool()>;
            using  TimerEv = TimerTask *;

    }
}


#endif /*_CALL_BACKS_H_ */
