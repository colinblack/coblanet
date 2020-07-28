#include "Listener.h"
#include <cstdio>
#include <cerrno>
#include <cstring>
#include "Logger.h"

void Listener::HandlerRead()
{
    sockaddr_in addr;
    socklen_t addrLen;
    int32_t sockFd = ::accept(listenFd_, reinterpret_cast<sockaddr *>(&addr), &addrLen);
    if (sockFd < 0)
    {
        LOG_ERROR("accept error:%s, %d \n", strerror(errno), errno);
        return;
    }
    InetAddr clientAddr(ntohs(addr.sin_port), inet_ntoa(addr.sin_addr));
    if (connectCB_)
    {
        connectCB_(sockFd, clientAddr);
    }
}


void Listener::GoListener()
{
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_.c_str());
    addr.sin_port = htons(port_);

    LOG_DEBUG("ip: %s \n", ip_.c_str());
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