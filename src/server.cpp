#include<server.hpp>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>

#ifdef DEBUG_MODE
    #define DEBUG_LOG(x) std::cout<<x<<std::endl;
#else
    #define DEBUG_LOG(x)
#endif

bool Server::createSocket(){
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd < 0){
        perror("Error Creating Socket");
        return false;
    }
    std::cout<<"Server Socket Creation Successful\n";
    return true;
}

bool Server::bindToAddress(std::string ip, int port){
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = port;
        if(!inet_pton(AF_INET,ip.data(),&serverAddress.sin_addr)){
            DEBUG_LOG("Invalid IP Passed ")
            return false;
        }
    if(bind(socketfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
        DEBUG_LOG("Binding Failed")
        return false;
    }
    return true;
}

bool Server::closeSocket(){
    close(socketfd);
    DEBUG_LOG("Socket Closed")
    return true;
}