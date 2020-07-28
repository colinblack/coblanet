#include "EventLoop.h"
#include "Channel.h"
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <errno.h>
#include "Logger.h"

using namespace flynet::net;

EventLoop::EventLoop()
   : epollFd_(::epoll_create1(EPOLL_CLOEXEC))
    ,eventData_(epollInitVaule)
{
    if(epollFd_ < 0){
        LOG_ERROR("epoll create error1:%s \n", strerror(errno));
    }
}

void EventLoop::loop()
{
    while (1)
    {
        int32_t evCnt = epoll_wait(epollFd_, &*eventData_.begin(), static_cast<int>(eventData_.size()), -1);
        if(evCnt > 0)
        {
            if(evCnt >= static_cast<int>(eventData_.size())){
                eventData_.resize(eventData_.size()*2);
            }
            for (int i = 0; i < evCnt; ++i)
            {
                auto &ev = eventData_[i];
                auto ch = reinterpret_cast<Channel *>(ev.data.ptr);
                if (ev.events & (EPOLLERR | EPOLLHUP))
                {
                }
                else if (ev.events & EPOLLIN)
                {
                    if(ch->readCB_)
                    {
                        LOG_DEBUG("readCB_ \n");
                       ch->readCB_();
                    }
                }
                else if (ev.events & EPOLLOUT)
                {
                    if(ch->writeCB_)
                    {
                        ch->writeCB_();
                    }
                }
                else
                {
                }
            }
        }else if(evCnt == 0)
        {
          LOG_DEBUG("haha, epoll even is null \n");
        }else
        {
            LOG_ERROR("epoll wait error:%s, %d \n", strerror(errno), errno);
        }
 
    }
}

void EventLoop::AddChannel(Channel *channel)
{
    epoll_event evData;
    memset(&evData, 0, sizeof evData);
    evData.events = channel->getEvent();
    evData.data.ptr = channel;
//    LOG_DEBUG("AddChannel, fd=%d,  event=%d, ptr=%p \n", channel->getFd(), channel->getEvent(), channel);
    int32_t ret = epoll_ctl(epollFd_, EPOLL_CTL_ADD, channel->getFd(), &evData);
    if (ret == -1)
    {
        LOG_ERROR("add epoll error::%s, %d \n", strerror(errno), errno);
    }
}

/* TimerEv  EventLoop::TimerStart(TimerTaskCallBack  cb,    uint64_t  after, uint64_t  repeat ){
    //timer
    //insert priority
   //settimer

} */
