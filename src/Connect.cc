#include "Connect.h"

Connect::Connect(EventLoop* loop):
    channel_(new Channel(loop))
{
    channel_->SetReadCallBack(NULL);
}

Connect::~Connect()
{
}

void Connect::ReadHandler(){

}
