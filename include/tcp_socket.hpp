//tcp_socket.hpp
#pragma once
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string>

class ServerSocket{
    private:
    int SocketFD=-1;
    sockaddr_in ServerAddress{};
    
    public: 
    sockaddr_in ConnectedClientAddress;
    bool CreateTCPSocket();
    bool BindTCPSocket(std::string ip,int port);
    void ListenTCPSocket(int backlog);
    void ConnectTCPSocket();
    void CloseTCPSocket();
    void PrintServerAddress();
};