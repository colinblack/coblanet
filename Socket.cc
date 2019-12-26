#include "Socket.h"

using  namespace  cobred;

void net::Socket(int32_t domain,  int32_t type, int32_t  protocol){	
    if(::socket(domain, type, protocol) < 0){
	exit(0);
    }
} 

void net::Bind(int32_t sockfd, const struct sockaddr *addr, socklen_t addrlen){
    if(::Bind(sockfd, addr, addrlen) < 0){
        exit(0);
    }
}

void net::Listen(int sockfd, int backlog){
    if(::listen(sockfd, backlog) < 0){
	exit(0);    
    }
}
int32_t net::Accept(int32_t sockfd, struct sockaddr *addr, socklen_t *addrlen){
    int32_t fd = 0; 	
    if((fd = ::accept(sockfd, addr, addrlen)) < 0){
    } 
 
    return fd;
}
