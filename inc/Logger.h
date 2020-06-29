#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <cstddef>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <alloca.h>
#include <utility>
#include <cstdlib>
#include <iostream>

    //日志buffer类
const int LogSamllBuffer = 4000;
const int LogLargeBuffer = 4000 * 1000;

template<std::size_t SIZE>
class LogBuffer{
public:
    void Append();
    uint8_t* GetBuffer(){
        return data_;
    }

    std::size_t Size(){
        return (sizeof data_);
    }
  void Clear(){
        memset(data_,  sizeof(data_), 0);
    }
private:
    uint8_t data_[SIZE];
};
    
//文件处理类
class  SrcFile{
public:
    template <int32_t  L>
    SrcFile(const char (&arr)[L])
        :data_(arr)
        ,size_(L-1){
        const char* pos = strrchr(arr,  '/');
        if(nullptr != pos){
            data_ = pos + 1;
            size_ -=  (data_ - arr); //这样做的效率比strlen 要高
        }
    }

    const char* Name(){
        return data_;
    }

private:
    const char* data_;
    int32_t  size_;
};

//单线程下饿汉单例
template <class T>
class CHSingleton
{
protected:
    CHSingleton()
    {
        _destory.init();
    }

    ~CHSingleton()
    {
    }

public:
    static T *Instance() { return _instance; }
    class CDestory
    {
    public:
        CDestory(){
       //     std::cout << "CDestory" << std::endl;
        }
        ~CDestory(){
        //  std::cout << "~CDestory" << std::endl;
        }
        static void init() {}
    };
   static  T* Allocate(){
        return new T;
    }

private:
//栈上分配内存
    void* operator new(std::size_t size) {
        return alloca(size);
    }
    thread_local static T *_instance;
    static CDestory _destory;
};

template <class T>
thread_local T *CHSingleton<T>::_instance = CHSingleton<T>::Allocate();

template <class T>
typename CHSingleton<T>::CDestory CHSingleton<T>::_destory;

//这里使用继承是为了方便使用成员函数，而非静态函数
class Logger : public CHSingleton<Logger>{
public:
    enum{
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
    };

public:
    //里面直接用c可变参
    template<class... Args>
    void  WriteLog(std::size_t level, const char* format, SrcFile file,  Args&&... args){
        commlog_.WriteLogEx(level, format, file, std::forward<Args>(args)...);
    }
    bool SetLevel(int32_t level){
        return commlog_.SetLevelEx(level);
    }

private:
//使用c++11方式
/*    template <class F,  class...  Args >
   void  WriteLogEx(const F&  first,  Args&...  args){
        WriteLogDetail(first);
   }

    template <class Value>
    void  WriteLogDetail(const Value   v){
    }    
   
   //c++特化可以这样写？
    void  WriteLogDetail(const char*  str){
        commlog_.Format(str);
    }     */

class CommonLog{
public:
        CommonLog();
        ~CommonLog();

public:
    using Buffer = LogBuffer<LogSamllBuffer>;
    void WriteLogEx(std::size_t lv, const char* fmt, SrcFile& file, ...); 
    bool SetLevelEx(int32_t level);
  
/*  
    void Format(std::size_t level, const char* format, SrcFile& file);
    void Format(const unsigned value);
    void Format(const char* value);
    void Format(double value);
    //小内存拷贝, 小于128字节
    //https://blog.csdn.net/ctthuangcheng/article/details/8915070
    //return：返回拷贝后的地址
     void  DefMemcpy(LogBuffer* dst, LogBuffer* src,){
        *dst = * src;
    } 
 */
private:
    int32_t  level_;
    FILE* fp_;
    Buffer buffer_;
};


private:
    friend class CHSingleton<Logger>;
    Logger(){
    }
    ~Logger(){
    }
    CommonLog   commlog_;
};


#define LOG_INFO(fmt, args...) \
do{ \
    Logger::Instance()->WriteLog(Logger::INFO, fmt,  __FILE__, __LINE__, __func__,  ##args); \
}while(0)

#define LOG_DEBUG(fmt, args...) \
do{ \
    Logger::Instance()->WriteLog(Logger::DEBUG,  fmt,  __FILE__, __LINE__, __func__, ##args); \
}while(0)

#define LOG_WARN(fmt, args...) \
do{ \
    Logger::Instance()->WriteLog(Logger::WARN,  fmt,  __FILE__, __LINE__,  __func__, ##args); \
}while(0)

#define LOG_ERROR(fmt, args...) \
do{ \
    Logger::Instance()->WriteLog(Logger::ERROR,  fmt,  __FILE__, __LINE__, __func__,  ##args); \
}while(0)

#define LOG_FATAL(fmt, args...) \
do{ \
    Logger::Instance()->WriteLog(Logger::FATAL,  fmt,  __FILE__, __LINE__, __func__,  ##args); \
}while(0)


#endif /*_LOGGER_H_  */
