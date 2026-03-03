//connection.cpp

#include<connection.hpp>
#include<iostream>
#ifdef DEBUG_MODE
    #define DEBUG_LOG(x) std::cout<<x<<std::endl;
#else
    #define DEBUG_LOG(x)
#endif

bool ClientConnection::getClientSession(int session){
    if(session < 0){
        DEBUG_LOG("\nInvalid Session\n")
        return false;
    }
    sessionfd = session;
    return true;
}

void ClientConnection::getClientAddress(const sockaddr_in cliAddr){
    clientAddress = cliAddr;
}

void ClientConnection::handleClient(){
    //whole client handling , from request parsing , response creation takes place here
}