//main.cpp
#include<iostream>
#include"../include/tcp_socket.hpp"

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: ./http_server <IP_ADDRESS>\n";
        return -1;
    }

    std::cout<<"Server Starting\n";
    ServerSocket Serv;
    if(!Serv.CreateTCPSocket()){
        perror("Error Creating Socket");
        return -1;
    }
    std::cout<<"Socket Creation Successful\n";
    if(!Serv.BindTCPSocket(argv[1],9000)){
        perror("Binding Socket Failed");
        Serv.CloseTCPSocket();
        return -1;
    }
    std::cout<<"Socket Binding Successfull\n";
    Serv.PrintServerAddress();

    if(!Serv.ListenTCPSocket(5)){
        perror("Error Listening : ");
        Serv.CloseTCPSocket();
        return -1;
    }
    std::cout<<":::::::::: Server Listening ::::::::::\n";
    while(1){
        if(!Serv.AcceptTCPSocket()){
            perror("Error Accepting Client");
            continue;
        }
        std::cout<<"Client Connected : ";
        Serv.PrintClientAddress();
        Serv.CloseClientSession();
    }

    Serv.CloseTCPSocket();
    return 0;
}