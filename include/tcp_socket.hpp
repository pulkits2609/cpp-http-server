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

    bool CreateTCPSocket();

    bool BindTCPSocket(std::string ip,int port);
    
    bool ListenTCPSocket(int backlog);
    
    bool AcceptTCPSocket();

    int GiveSessionFD(); //this will be used by http_handler to get sessionFD

    void PrintClientAddress();

    bool ReadClientRequest(); //used to parse the method requested by the client

    bool WriteClientRequest();//send appropriate response to client

    void CloseClientSession();
    
    void CloseTCPSocket();
    
    void PrintServerAddress();


    //////////DEBUGGING FUNCTIONS , NOT SAFE FOR PRODUCTION
    void ClientMessageStream();
};