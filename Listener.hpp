#include "Channel.h"
#include "Socket.h"
#include "InetAddr.h"
#include <functional>
#include <arpa/inet.h>

class Listener
{
public:
    using ConnectCallback = std::function(void(int32_t, InetAddr &));
    Listener(/* args */)
    {
    }
    ~Listener()
    {
    }

private:
    Channel listenChan_;
    int32_t listenFd_;
    ConnectCallback connectCB_;

    void SetConnectCallback(ConnectCallback cb)
    {
        connectCB_ = std::move(cb);
    }

    void HandlerRead(void *argc)
    {
        sockaddr_in addr;
        int32_t sockFd = ::accept(listenFd_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
        if (sockFd < 0)
        {
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

    void GoListener()
    {
        int32_t listenFd_ = Socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip_.c_str());
        addr.sin_port = htons(port_);

        Bind(listenFd_, &addr, sizeof(addr));
        Listen(listenFd_, 10);
        listenChan_.SetFd(listenFd_);
        listenChan_.SetReadCallBack(std::bind(&Listener::HandlerRead, this));
    }
};
