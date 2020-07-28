#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include <functional>
#include <sys/epoll.h>

namespace flynet{
namespace net{

class EventLoop;

class Channel
{
public:
    Channel(EventLoop *loop,  int32_t fd)
        : loop_(loop)
        , event_(0)
        , fd_(fd)
    {
    }

public:
    using ReadCallbackFunc = std::function<void()>;
    using WriteCallbackFunc = std::function<void()>;
    using ExceptionCallbackFunc = std::function<void()>;

    void HandlerReadEv();
    void EnableReading();
    void EnableWriting();
    void DisableRead();
    void DisableWrite();
    int32_t getFd(){
        return fd_;
    }

    void SetFd(int32_t fd){
        fd_ = fd;
    }
    int32_t getEvent(){
        return event_;
    }

    void SetReadCallBack(ReadCallbackFunc bc){
        readCB_ = std::move(bc);
    }

    void SetWriteCallBack(WriteCallbackFunc bc){
        writeCB_ = std::move(bc);
    }

    ReadCallbackFunc readCB_;
    WriteCallbackFunc writeCB_;
    ExceptionCallbackFunc ExceptionCB_;

private:
    EventLoop *loop_;
    int32_t event_;
    int32_t fd_;
};


}

}

#endif /*_CHANNEL_H_*/
