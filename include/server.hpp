//server.hpp
//handles :
//  socket creation
//  bind
//  listen
//  accept loop
//  thread pool integration (YET TO BE IMPLEMENTED)

//mainly this will be handling server lifecycle

#pragma once
#include<iostream>
#include<arpa/inet.h>
#include<string>
#include<router.hpp> //server will own the router , not client
#include<thread_pool.hpp>

class Server{
    private:
    int socketfd = -1;
    sockaddr_in serverAddress{};
    Router router{};
    ThreadPool* threadPool = nullptr;

    public:
    bool createSocket();
    bool bindToAddress(std::string ip, int port);
    bool startListening(int backlog);
    void acceptLoop();
    bool closeSocket();
    Router& giveRouterInstance();
};
