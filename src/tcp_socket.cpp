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

bool ServerSocket::ListenTCPSocket(int backlog){
    int ret=listen(SocketFD,backlog);
    if(ret < 0)return false;
    return true;
}

bool ServerSocket::AcceptTCPSocket(){
    memset(&ConnectedClientAddress,0,sizeof(ConnectedClientAddress));
    socklen_t len = sizeof(ConnectedClientAddress);

    SessionFD = accept(SocketFD,(struct sockaddr*)&ConnectedClientAddress,&len);
    if(SessionFD < 0){
        return false;
    }
    return true;
}

void ServerSocket::PrintClientAddress(){
    char CLIENT_IP[INET_ADDRSTRLEN];
    if(!inet_ntop(AF_INET,&ConnectedClientAddress.sin_addr,CLIENT_IP,INET_ADDRSTRLEN)){
        perror("inet_atop failed :");
    }
    else{
        std::cout<<"Address : "<<CLIENT_IP<<":"<<ntohs(ConnectedClientAddress.sin_port)<<"\n";
    }
}

void ServerSocket::CloseTCPSocket(){
    close(SocketFD);
}

void ServerSocket::CloseClientSession(){
    close(SessionFD);
}

void ServerSocket::PrintServerAddress(){
    std::cout<<"Server Address : "<<inet_ntoa(ServerAddress.sin_addr)<<":"<<ntohs(ServerAddress.sin_port)<<"\n";
}