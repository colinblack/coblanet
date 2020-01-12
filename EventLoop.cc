#include "EventLoop.h"
#include "Channel.h"

EventLoop::EventLoop()
    : epollFd_(::epoll_create1(FD_CLOEXEC))
{
}

void EventLoop::loop()
{
    while (1)
    {
        int32_t evCnt = epoll_wait(epollFd_, &*eventData_.begin(), eventData.size(), 0);
        for (int i = 0; i < evCnt; ++i)
        {
            auto &ev = eventData_[i];
            auto ch = reinterpret_cast<Channel*>(ev.data.ptr);
            if(ev.events & (EPOLLERR|EPOLLHUP)){
	        }else if(ev.events & EPOLLIN){
                ch->readCB_();
	        }else if(ev.events & EPOLLOUT){

	        }else{

	        }
        }
    }
}

void EventLoop::AddChannel(Channel *channel)
{
    epoll_event evData;
    evData.events = channel->getEvent();
    evData.data.ptr = channel;
    int32_t ret = epoll_ctl(epollFd_, EPOLL_CTL_ADD, channel->getFd(), &evData);
    if (ret == -1)
    {
    }
}
