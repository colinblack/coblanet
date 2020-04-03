#include "Connect.h"
#include <functional>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

Connect::Connect(EventLoop* loop, int16_t fd, InetAddr& addr)
    : addr_(addr)
    , channel_(new Channel(loop))
    , pBuff_(new char[buffSize_])
{
    channel_->SetReadCallBack(std::bind(&Connect::ReadHandler, this));
    channel_->SetWriteCallBack(std::bind(&Connect::WriteHandler, this));
    channel_->SetFd(fd);
}

Connect::~Connect()
{
}

void Connect::ReadHandler(){
    read(channel_->getFd(), pBuff_.get(), buffSize_);
    if(messageCallback_ != nullptr){
        messageCallback_();
    }
    printf("%s \n", pBuff_.get());
    channel_->EnableWriting();
}

void Connect::WriteHandler(){
    int32_t ret = write(channel_->getFd(), pBuff_.get(), buffSize_);
    if(ret < 0){
        printf("send data error:%s, %d \n", strerror(errno), errno);
    }
}

void Connect::ConnectEstabished(){
    channel_->EnableReading();
}

void Connect::SetMessageCallback(const MessageCallback& cb){
    messageCallback_ = cb;
}