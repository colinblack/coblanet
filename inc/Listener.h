#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "Channel.h"
#include "Socket.h"
#include "InetAddr.h"
#include <functional>
#include <arpa/inet.h>


using namespace cobred::net;
class Listener
{
public:
    Listener(EventLoop *loop, int16_t port, std::string ip) 
        : listenChan_(loop)
        , port_(port)
        , ip_(ip)
    {
    }
    ~Listener()
    {
    }
    using ConnectCallback = std::function<void(int32_t, InetAddr &)>;

private:
    Channel listenChan_;
    int32_t listenFd_;
    int16_t port_;
    std::string ip_;
    ConnectCallback connectCB_;

public:
    void SetConnectCallback(ConnectCallback cb);
    void HandlerRead();
    void GoListener();
};

#endif /*_LISTENER_H_*/
