#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <tuple>
#include <memory>
#include <map>
#include "Listener.h"
#include "Connect.h"
#include <string>
#include "Socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <functional>
#include <memory>

using namespace cobred::net;
class EventLoop;
class TcpServer
{
public:
    TcpServer(EventLoop* loop)
        : loop_(loop)
        , conId_(1)
    {
    }
    void Start(int16_t port, const std::string &&ip);
private:
    void NewConnection(int32_t fd, InetAddr & addr);

private:
    using ConnectMap = std::map<std::string, std::shared_ptr<Connect>>;
    std::shared_ptr<Listener> listener_;
    ConnectMap connsMap_; 
    EventLoop* loop_;
    int64_t conId_;
};



#endif /* _TCP_SERVER_H_ */
