#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include "EventLoop.h"
#include <functional>

class EventLoop;
class Channel
{
public:
    Channel(EventLoop *loop)
        : loop_(loop)
        , event_(0)
        , fd_(0)
    {
    }

public:
    using ReadCallbackFunc = std::function<void()>;
    using WriteCallbackFunc = std::function<void()>;
    using ExceptionCallbackFunc = std::function<void()>;

    void HandlerReadEv()
    {
        if (readCB_)
        {
            readCB_();
        }
    }
    void EnableReading()
    {
        event_ |= EPOLLIN;
        loop_->AddChannel(this);
    }

    void EnableWriting(){
        event_ |= EPOLLOUT;
        loop_->AddChannel(this);
    }

    void DisableRead(){
        event_ &= ~EPOLLIN;
    }
    void DisableWrite(){
        event_ &= ~EPOLLOUT;
    }
    int32_t getFd()
    {
        return fd_;
    }

    void SetFd(int32_t fd)
    {
        fd_ = fd;
    }
    int32_t getEvent()
    {
        return event_;
    }

    void SetReadCallBack(ReadCallbackFunc bc)
    {
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

#endif /*_CHANNEL_H_*/
