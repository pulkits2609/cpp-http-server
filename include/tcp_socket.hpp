//tcp_socket.hpp
//transport layer abstraction
#pragma once
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string>

class ServerSocket{
    private:
    int SocketFD=-1;

    int SessionFD=-1; //for now single SessionFD To manage single Cient at a time (BLOCKING)
    
    sockaddr_in ServerAddress{};
    
    public: 
    sockaddr_in ConnectedClientAddress{};

    bool createTCPSocket();

    bool bindTCPSocket(std::string ip,int port);
    
    bool listenTCPSocket(int backlog);
    
    bool acceptTCPSocket();

    int giveSessionFD(); //this will be used by http_handler to get sessionFD

    void printClientAddress();

    bool readClientRequest(); //used to parse the method requested by the client

    bool writeClientResponse(const std::string& Response);//send appropriate response to client

    void closeClientSession();
    
    void closeTCPSocket();
    
    void printServerAddress();


    //////////DEBUGGING FUNCTIONS , NOT SAFE FOR PRODUCTION
    void clientMessageStream();
};