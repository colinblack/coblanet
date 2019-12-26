#include "EventLoop.h"


EventLoop::EventLoop()
    : eventFd_(::epoll_create1(FD_CLOEXEC))
{    
}

void EventLoop::loop()
{
    while(1){
        int32_t fdNum = epoll_wait(eventFd_, &*eventData_.begin(); eventData_.size(), 0);


    }

}

void  EventLoop::AddChannel(Channel* channel){
    epoll_event evData;
    evData.events = channel->getEvent();
    evData.data.ptr = channel;
    int32_t ret = epoll_ctl(eventFd_, EPOLL_CTL_ADD, channel->getFd(), &evData);
    if (ret < 0){

    }

}