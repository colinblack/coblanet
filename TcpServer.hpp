#ifndef   _TCP_SERVER_HPP_
#define  _TCP_SERVER_HPP_

#include <tuple>
#include <memory>
#include <map>
#include "Listener.hpp"
#include "Connect.hpp"
#include <string>
#include "Socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

}

#endif  /* _TCP_SERVER_HPP_ */
