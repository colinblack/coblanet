#include "EventLoop.h"

class Channel{
public:
    Channel(EventLoop* loop) 
        : loop_(loop), event_(0), fd(0){
            
    }
public:
    void EnableReading(){
        event_ |= EPOLLIN;
        loop_->AddChannel(this);
    }

    int32_t getFd(){
        return fd_;
    }
    int32_t getEvent(){
        return event_;
    }

private:
    EventLoop* loop_;
    int32_t event_;
    int32_t fd_;
};
