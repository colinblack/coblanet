#ifndef _TCP_SERVER_HPP_
#define _TCP_SERVER_HPP_

#include <tuple>
#include <memory>
#include <map>
#include "Listener.hpp"
#include "Connect.hpp"
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
    TcpServer()
    {
    }
    void Start(EventLoop *loop, int16_t port, std::string &ip);

public:
    std::shared_ptr<Listener> listener_;
    std::map<std::string, Connect> conns_;
    void NewConnection();
};

void TcpServer::Start(EventLoop *loop, int16_t port, std::string &ip)
{
    listener_ = std::make_shared<Listener>(new Listener(loop, port, ip));
    listener_->GoListener();
    listener_->SetConnectCallback(std::bind(&TcpServer::NewConnection, this));
}

#endif /* _TCP_SERVER_HPP_ */
