#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stdint.h>
const uint32_t BUFFER_SIZE = 512;
class Buffer{
public:
    Buffer();
    Buffer(uint32_t capacity);
    ~Buffer();
public:
    uint8_t* GetNativeBuffer();
    void Resize(uint32_t size);
    uint32_t Size();
    uint32_t Capacity();

private:
    uint8_t *pBuffer_;
    uint32_t size_;
    uint32_t capacity_;
};


#endif