//main.cpp
#include<iostream>
#include"tcp_socket.hpp"
#include"http_handler.hpp"
#include<server.hpp>

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: ./http_server <IP_ADDRESS>\n";
        return -1;
    }

    Server Srv;
    if(!Srv.createSocket()){
        return -1;
    }
    if(!Srv.bindToAddress(argv[1],9000)){
        Srv.closeSocket();
        return -1;
    }
    Srv.acceptLoop();
    Srv.closeSocket();
    // std::cout<<"Server Starting\n";
    // ServerSocket server_socket;
    // if(!server_socket.createTCPSocket()){
    //     perror("Error Creating Socket");
    //     return -1;
    // }
    // std::cout<<"Socket Creation Successful\n";
    // if(!server_socket.bindTCPSocket(argv[1],9000)){
    //     perror("Binding Socket Failed");
    //     server_socket.closeTCPSocket();
    //     return -1;
    // }
    // std::cout<<"Socket Binding Successfull\n";
    // server_socket.printServerAddress();

    // if(!server_socket.listenTCPSocket(5)){
    //     perror("Error Listening : ");
    //     server_socket.closeTCPSocket();
    //     return -1;
    // }
    // std::cout<<":::::::::: Server Listening ::::::::::\n";
    // while(1){
    //     if(!server_socket.acceptTCPSocket()){
    //         perror("Error Accepting Client");
    //         continue;
    //     }
    //     std::cout<<"Client Connected : ";
    //     server_socket.printClientAddress();
        
    //     HttpHandler http_handler{};
    //     http_handler.getSessionFD(server_socket.giveSessionFD());
    //     http_handler.readClientRequest();
    //     http_handler.printClientRequestString();

    //     if(!server_socket.writeClientResponse(http_handler.sendClientResponse())){
    //         perror("Error Writing Response to Client : ");
    //     }
    //     std::cout<<"\nSent Client Response !\n";

    //     //server_socket.ClientMessageStream();
    //     server_socket.closeClientSession();  
    // }
    
    // server_socket.closeTCPSocket();
    return 0;
}