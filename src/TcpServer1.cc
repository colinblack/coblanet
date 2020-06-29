#include "TcpServer1.h"
#include <cstdio>
#include <string>

using namespace std::placeholders;
void TcpServer1::Start(InetAddr& addr)
{
    listener_ = std::make_shared<Listener>(loop_, addr.port_, addr.ip_);
    listener_->GoListener();
    listener_->SetConnectCallback(std::bind(&TcpServer1::NewConnection, this, _1, _2));
}

EventLoop* TcpServer1::GetLoop(){
    return loop_;
}

void TcpServer1::NewConnection(int32_t fd, InetAddr & addr)
{
    std::shared_ptr<Connect> con(new Connect(loop_, fd, addr));
    con->ConnectEstabished();
    con->SetMessageCallback(messageCallback_);
    char buf[64];
    snprintf(buf, sizeof buf, "%ld", conId_);
    std::string strId(buf);
    connsMap_[strId] = con;
} 

void TcpServer1::SetMessageCallback(const MessageCallback& cb){
    messageCallback_ = cb;
}

bool TcpServer1::DefaultMessage(){

    return true;
}