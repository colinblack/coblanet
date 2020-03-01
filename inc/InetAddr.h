#ifndef  _INETADDR_H_
#define  _INETADDR_H_

#include <stdint.h>
#include <string>

class InetAddr
{
public:
    InetAddr();
    InetAddr(uint16_t , std::string);
    ~InetAddr();

public:
    uint16_t port_;
    std::string ip_;
};



#endif /*_INETADDR_H_*/
