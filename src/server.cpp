//server.cpp

#include<server.hpp>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include<connection.hpp>

bool Server::createSocket(){
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd < 0){
        perror("Error Creating Socket");
        return false;
    }
    int opt=1;
    if(setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))){
        perror("setsockopt failed :");
        return false;
    }
    std::cout<<"Server Socket Creation Successful\n";
    return true;
}

bool Server::bindToAddress(std::string ip, int port){
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
        if(!inet_pton(AF_INET,ip.data(),&serverAddress.sin_addr)){
            std::cout<<"Invalid IP Passed\n";
            return false;
        }
    if(bind(socketfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
        perror("Binding Failed : ");
        return false;
    }
    std::cout<<"Binding Successful at Address : "<<inet_ntoa(serverAddress.sin_addr)<<":"<<ntohs(serverAddress.sin_port)<<"\n";
    return true;
}

bool Server::startListening(int backlog){
    if(listen(socketfd,backlog) < 0){
        perror("Error Listening : ");
        return false;
    }
    std::cout<<":::::::::Server Listening::::::::\n";
    return true;
}

void Server::acceptLoop(){
    while(1){
        sockaddr_in clientAddress{};
        socklen_t cliLength= sizeof(clientAddress);
        ClientConnection clientConnection{};
        if(!clientConnection.getClientSession(accept(socketfd,(struct sockaddr*)&clientAddress,&cliLength))){
            //meaning that if the Session FD is invalid
            continue;
        };
        clientConnection.getClientAddress(clientAddress);
        clientConnection.handleClient();
    }
}

bool Server::closeSocket(){
    close(socketfd);
    std::cout<<"::::::::Server Closed::::::\n";
    return true;
}