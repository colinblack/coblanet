#ifndef  _CONNECT_H_
#define  _CONNECT_H_

#include "InetAddr.h"
#include <sys/epoll.h>
#include "Channel.h"
#include <memory>

class Connect
{
public:
    Connect(EventLoop* loop, int16_t fd, InetAddr& addr);
    ~Connect();
    void ReadHandler();
    void WriteHandler();
    void ConnectEstabished();
private:
    static const int32_t buffSize_ = 64;
    InetAddr addr_;
    std::unique_ptr<Channel> channel_;
    std::unique_ptr<char> pBuff_;
    
};


#endif /*_CONNECT_H_*/
