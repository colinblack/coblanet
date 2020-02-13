#ifndef  _INETADDR_H_
#define  _INETADDR_H_

#include <stdint.h>
#include <string>

struct InetAddr
{
    int16_t port_;
    std::string ip_;

    InetAddr(/* args */);
    ~InetAddr();
};



#endif /*_INETADDR_H_*/
