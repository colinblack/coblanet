#include "InetAddr.h"
#include <sys/epoll.h>

class Connect
{
private:
    /* data */
public:
    Connect(/* args */);
    ~Connect();

public:
    void NewConnect(int32_t sock, InetAddr &addr);
};

Connect::Connect(/* args */)
{
}

Connect::~Connect()
{
}

void Connect::NewConnect(int32_t sock, InetAddr &addr)
{
    epoll_create()
}