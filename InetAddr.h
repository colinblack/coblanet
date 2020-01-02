#include <stdint.h>
#include <string>

struct InetAddr
{
    int16_t port_;
    std::string ip_;

    InetAddr(/* args */);
    ~InetAddr();
};

InetAddr::InetAddr(/* args */)
{
}

InetAddr::~InetAddr()
{
}
