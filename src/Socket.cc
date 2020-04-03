#include "Socket.h"
#include <stdlib.h>

using namespace flynet;

int32_t net::Socket(int32_t domain, int32_t type, int32_t protocol)
{
    int32_t fd = 0;
    if ((fd = ::socket(domain, type, protocol)) < 0)
    {
        exit(0);
    }

    return fd;
}

void net::Bind(int32_t sockfd, const sockaddr *addr, socklen_t addrlen)
{
    if (::bind(sockfd, addr, addrlen) < 0)
    {
        exit(0);
    }
}

void net::Listen(int sockfd, int backlog)
{
    if (::listen(sockfd, backlog) < 0)
    {
        exit(0);
    }
}
int32_t net::Accept(int32_t sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int32_t fd = 0;
    if ((fd = ::accept(sockfd, addr, addrlen)) < 0)
    {
    }

    return fd;
}
