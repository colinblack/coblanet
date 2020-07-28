#include  "Channel.h"
#include  "EventLoop.h"

using namespace flynet::net;


   void Channel::HandlerReadEv()
    {
        if (readCB_)
        {
            readCB_();
        }
    }
    void Channel::EnableReading()
    {
        event_ |= EPOLLIN;
        loop_->AddChannel(this);
    }

    void Channel::EnableWriting(){
        event_ |= EPOLLOUT;
        loop_->AddChannel(this);
    }

    void Channel::DisableRead(){
        event_ &= ~EPOLLIN;
    }
    void Channel::DisableWrite(){
        event_ &= ~EPOLLOUT;
    }
