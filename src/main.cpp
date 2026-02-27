//main.cpp
#include<iostream>
#include"../include/tcp_socket.hpp"

int main(){
    std::cout<<"Server Starting\n";
    ServerSocket SSocket;
    if(!SSocket.CreateTCPSocket()){
        perror("Error Creating Socket");
        return -1;
    }
    std::cout<<"Socket Creation Successful\n";
    if(!SSocket.BindTCPSocket("127.0.0.1",9000)){
        perror("Binding Socket Failed");
        SSocket.CloseTCPSocket();
        return -1;
    }
    std::cout<<"Socket Bindind Successfull\n";

    SSocket.CloseTCPSocket();
    return 0;
}