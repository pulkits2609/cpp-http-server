//server.hpp
//handles :
//  socket creation
//  bind
//  listen
//  accept loop
//  thread pool integration (YET TO BE IMPLEMENTED)

//mainly this will be handling server lifecycle

#include<iostream>
#include<arpa/inet.h>
#include<string>

class Server{
    private:
    int socketfd = -1;
    sockaddr_in serverAddress{};

    public:
    bool createSocket();
    bool bindToAddress(std::string ip, int port);
    bool startListening(int backlog);
    void acceptLoop();
    bool closeSocket();
};
