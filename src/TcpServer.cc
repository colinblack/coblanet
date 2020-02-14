#include "TcpServer.h"
#include <cstdio>
#include <string>

using namespace std::placeholders;
void TcpServer::Start(int16_t port, const std::string &&ip)
{
    listener_ = std::make_shared<Listener>(loop_, port, ip);
    listener_->GoListener();
    listener_->SetConnectCallback(std::bind(&TcpServer::NewConnection, this, _1, _2));
}

void TcpServer::NewConnection(int32_t fd, InetAddr & addr)
{
    std::shared_ptr<Connect> con(new Connect(loop_, fd, addr));
    con->ConnectEstabished();
    char buf[64];
    snprintf(buf, sizeof buf, "%ld", conId_);
    std::string strId(buf);
    connsMap_[strId] = con;
} 
