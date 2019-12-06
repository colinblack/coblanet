#ifndef   _TCP_SERVER_HPP_
#define  _TCP_SERVER_HPP_

#include <tuple>
template <class ... Types>
class TcpServer{
public:
    constexpr TcpServer(){};
    constexpr TcpServer(Types& ... args){

    }

};



#endif  /* _TCP_SERVER_HPP_ */
