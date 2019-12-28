#include "Channel.h"
#include "Socket.h"

class Listener
{
private:
    Channel listenChan_; 
    int32_t listenFd_;

public:
    Listener(/* args */){

    }
    ~Listener(){
	

    }
	
    void HandlerRead(void* argc){
	sockaddr addr; 
    	int32_t sockFd = ::accept(listenFd_, &addr, sizeof(addr));
	if(sockFd < 0){
	    return 0;	
	}
    
    }
    void GoListener(){
        int32_t listenFd_ = Socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in  addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip_.c_str());
        addr.sin_port = htons(port_);

        Bind(listenFd_, &addr, sizeof(addr));
        Listen(listenFd_, 10);
        listenChan_.SetFd(listenFd_); 
      	listenChan_.SetReadCallBack(std::bind(&Listener::HandlerRead, this));	
    }

};
