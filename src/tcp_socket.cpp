//tcp_socket.cpp
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include"tcp_socket.hpp"
#define MAX_ALLOWED 1024

bool ServerSocket::CreateTCPSocket(){
    SocketFD = socket(AF_INET,SOCK_STREAM,0); //create TCP Socket
    if(SocketFD < 0){
        return false;
    }
    int opt=1;
    if(setsockopt(SocketFD,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))){
        perror("setsockopt failed :");
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

int ServerSocket::GiveSessionFD(){
    return SessionFD;
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

/////////////////////////////debugging functions
void ServerSocket::ClientMessageStream(){
    int ret=-1;
    char ReadBuff[1024]{};
    size_t ReadBytes=0;
    std::cout<<"\n::::::::::Client Message Stream::::::::::::\n";
    while(1){
        memset(&ReadBuff,0,sizeof(ReadBuff)); 
        ret = read(SessionFD,&ReadBuff,sizeof(ReadBuff));
        if(ret < -1){
            perror("Error Reading from client :");
            break;
        }
        else if(ret == 0){
            std::cout<<"\n::::::::::::::::\nEnd of Client Message Stream\n";
            std::cout<<"Bytes Read : "<<ReadBytes<<"\n";
            break;
        }
        else{
            ReadBytes+=ret;
            std::cout.write(ReadBuff,ret); //write the exact number of bytes read ! 
        }
    }
}