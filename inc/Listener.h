#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "Channel.h"
#include "Socket.h"
#include "InetAddr.h"
#include <functional>
#include <arpa/inet.h>


using namespace flynet::net;
class Listener
{
public:
    Listener(EventLoop *loop, int16_t port, std::string ip) 
        :listenFd_(Socket(AF_INET, SOCK_STREAM, 0))
        , port_(port)
        , ip_(ip)
        ,listenChan_(loop, listenFd_)
    {
    }
    ~Listener()
    {
    }
    using ConnectCallback = std::function<void(int32_t, InetAddr &)>;

private:
    int32_t listenFd_;
    int16_t port_;
    std::string ip_;
    Channel listenChan_;
    ConnectCallback connectCB_;

public:
    void SetConnectCallback(ConnectCallback cb);
    void HandlerRead();
    void GoListener();
};

#endif /*_LISTENER_H_*/
