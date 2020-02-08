#ifndef  _CONNECT_HPP_
#define  _CONNECT_HPP_


#include "InetAddr.h"
#include <sys/epoll.h>

class Connect
{
public:
    Connect(/* args */);
    ~Connect();
    void ReadHandler();

};

Connect::Connect(/* args */)
{
}

Connect::~Connect()
{
}

void Connect::ReadHandler(){



}

#endif /*_CONNECT_HPP_*/
