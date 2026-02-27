//tcp_socket.cpp
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include"tcp_socket.hpp"
#define MAX_ALLOWED 512

bool ServerSocket::CreateTCPSocket(){
    SocketFD = socket(AF_INET,SOCK_STREAM,0); //create TCP Socket
    if(SocketFD < 0){
        return false;
    }
    return true;
};

bool ServerSocket::BindTCPSocket(std::string ip,int port){
    if(!inet_pton(AF_INET,ip.data(),&ServerAddress.sin_addr)){
        return false;
    }
    ServerAddress.sin_family=AF_INET;
    ServerAddress.sin_port=htons(port);
    int ret = bind(SocketFD,(struct sockaddr* )&ServerAddress,sizeof(ServerAddress));
    if(ret < 0) return false;
    return true;
}

void ServerSocket::CloseTCPSocket(){
    close(SocketFD);
}

void ServerSocket::PrintServerAddress(){
    std::cout<<"Server Address : "<<inet_ntoa(ServerAddress.sin_addr)<<":"<<ntohs(ServerAddress.sin_port)<<"\n";
}