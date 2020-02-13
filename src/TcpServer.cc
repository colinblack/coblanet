#include "TcpServer.h"
#include <cstdio>
#include <string>
     
void TcpServer::Start(int16_t port, std::string &ip)
{
    listener_ = std::make_shared<Listener>(loop_, port, ip);
    listener_->GoListener();
    listener_->SetConnectCallback(std::bind(&TcpServer::NewConnection, this));
}

void TcpServer::NewConnection()
{
    std::shared_ptr<Connect> con(new Connect(loop_));
    char buf[64];
    snprintf(buf, sizeof buf, "%ld", conId_);
    std::string strId(buf);
    connsMap_[strId] = con;
} 
