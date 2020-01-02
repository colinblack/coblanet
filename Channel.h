#include "EventLoop.h"
#include <functional>

class Channel{
public:
    Channel(EventLoop* loop)
        : loop_(loop), event_(0), fd(0){

    }
public:
    using function<void(void*)> ReadCallbackFunc;

    void HandlerReadEv(){
    	if(readCB_){
	    readCB_();
	}
    }
    void EnableReading(){
        event_ |= EPOLLIN;
        loop_->AddChannel(this);
    }

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
        radCB_ = std::move(bc);
    }

private:
    EventLoop* loop_;
    int32_t event_;
    int32_t fd_;
    ReadCallbackFunc readCB_;
};
