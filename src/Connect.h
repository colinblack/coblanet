#ifndef  _CONNECT_H_
#define  _CONNECT_H_

#include "InetAddr.h"
#include <sys/epoll.h>
#include "Channel.h"
#include <memory>

class Connect
{
public:
    Connect(EventLoop* loop);
    ~Connect();
    void ReadHandler();
private:
    std::unique_ptr<Channel> channel_;
};


#endif /*_CONNECT_H_*/
