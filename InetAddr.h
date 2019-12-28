#include <stdint.h>
#include <string>

class InetAddr
{
private:
    int16_t port_;
    std::string ip_;

public:
    InetAddr(/* args */);
    ~InetAddr();
};

InetAddr::InetAddr(/* args */)
{
}

InetAddr::~InetAddr()
{
}
