#include "InetAddr.h"

InetAddr::InetAddr(){
}

InetAddr::InetAddr(uint16_t port, std::string ip)
    : port_(port)
    , ip_(ip) 
{
}

InetAddr::~InetAddr()
{
}

