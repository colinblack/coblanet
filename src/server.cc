#include "TcpServer1.h"


int main(){
    EventLoop* loop = new EventLoop;
    TcpServer1 srv(loop);
    InetAddr addr(888, "182.254.170.197");
    srv.Start(addr);
    loop->loop();
    
    return 0;
}
