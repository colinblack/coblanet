#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>

namespace flynet {
    namespace net{
        int32_t Socket(int32_t domain, int32_t type, int32_t protocol);
        void Bind(int32_t sockfd, const sockaddr *addr, socklen_t addrlen);
        void Listen(int sockfd, int backlog);
        int32_t Accept(int32_t sockfd, struct sockaddr *addr, socklen_t *addrlen);
    } // namespace net
} // namespace flynet
 
#endif /*_SOCKET_H_*/
