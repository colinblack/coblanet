#include "Buffer.h"

Buffer::Buffer()
: pBuffer_(new uint8_t[BUFFER_SIZE]){

}

Buffer::Buffer(uint32_t capacity)
: pBuffer_(new uint8_t[capacity]){

}

Buffer::~Buffer(){
    delete pBuffer_;
}


uint32_t Buffer::Size(){
    return size_;
}

uint32_t Buffer::Capacity(){
    return capacity_;
}

uint8_t* Buffer::GetNativeBuffer(){
    return pBuffer_;
}

void Buffer::Resize(uint32_t size){
    if(size > size_ && size <= capacity_){
        size_ = size;
    }
}