#ifndef _TCP_SERVER1_H_
#define _TCP_SERVER1_H_

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
#include "InetAddr.h"

using namespace cobred::net;
class EventLoop;
class TcpServer1
{
public:
    TcpServer1(EventLoop* loop)
        : loop_(loop)
        , conId_(1)
    {
    }
    void Start(InetAddr& addr);
    EventLoop* GetLoop();
private:
    void NewConnection(int32_t fd, InetAddr & addr);

private:
    using ConnectMap = std::map<std::string, std::shared_ptr<Connect>>;
    std::shared_ptr<Listener> listener_;
    ConnectMap connsMap_; 
    EventLoop* loop_;
    int64_t conId_;
};



#endif /* _TCP_SERVER1_H_ */
