#ifndef   _TCP_SERVER_HPP_
#define  _TCP_SERVER_HPP_

#include <tuple>
#include <memory>
#include <map>
#include  "Listener.hpp"
#include "Connect.hpp"
#include <string>
#include "Socket.h"

using namespace cobred::net;
class TcpServer{
public:
     TcpServer(int16_t port, int16_t ip):
         port_(port), ip_(ip)
     {
     }
     void Start();  

public:
    std::shared_ptr<Listener>  listener_;
    std::map<std::string, Connect > conns_;

private:
    int16_t port_;
    std::string ip_;
};


void TcpServer::Start(){
    int32_t listenFd = Socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in  addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_.c_str());
    addr.sin_port = htons(port_);

    Bind(listenFd, &addr, sizeof(addr));
    Listen(listenFd, 10);

}

#endif  /* _TCP_SERVER_HPP_ */
