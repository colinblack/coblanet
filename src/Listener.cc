#include "Listener.h"
#include <cstdio>
#include <cerrno>
#include <cstring>

void Listener::HandlerRead()
{
    sockaddr_in addr;
    socklen_t addrLen;
    int32_t sockFd = ::accept(listenFd_, reinterpret_cast<sockaddr *>(&addr), &addrLen);
    if (sockFd < 0)
    {
        printf("accept error:%s, %d \n", strerror(errno), errno);
        return;
    }
    InetAddr clientAddr;
    clientAddr.port_ = ntohs(addr.sin_port);
    clientAddr.ip_ = inet_ntoa(addr.sin_addr);
    if (connectCB_)
    {
        connectCB_(sockFd, clientAddr);
    }
}


void Listener::GoListener()
{
    listenFd_ = Socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_.c_str());
    addr.sin_port = htons(port_);

    Bind(listenFd_, reinterpret_cast<const sockaddr *>(&addr), sizeof(addr));
    Listen(listenFd_, 10);
    listenChan_.SetFd(listenFd_);
    listenChan_.EnableReading();
    listenChan_.SetReadCallBack(std::bind(&Listener::HandlerRead, this));
}

void Listener::SetConnectCallback(ConnectCallback cb)
{
    connectCB_ = std::move(cb);
}