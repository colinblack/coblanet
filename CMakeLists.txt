cmake_minimum_required(VERSION 3.15)
project(cobred)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cobred
        Channel.h
        Connect.hpp
        EventLoop.cc
        EventLoop.h
        InetAddr.h
        Listener.hpp
        main.cc
        Poll.h
        Socket.cc
        Socket.h
        TcpServer.hpp)
