#include   "TcpServer.h"

int  main()
{
    EventLoop* loop = new EventLoop;
    TcpServer srv(loop);
    srv.Start(3368, "192.168.1.102");
    loop->loop();    
    delete loop;
    return  0;    
}