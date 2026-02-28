//http_handler.cpp

#include<iostream>
#include "../include/http_handler.hpp"
#include<unistd.h>
#include<cstring>

void http_handler::GetSessionFD(int SesFd){
    SessionFD=SesFd; //no need to check because ServerHandler will return correct FD
}

void http_handler::ReadClientRequest(){
    char ReadBuffer[512]{};

    while (RequestString.find("\r\n\r\n") == std::string::npos){
        memset(ReadBuffer,0,sizeof(ReadBuffer));
        int ret = read(SessionFD,ReadBuffer,sizeof(ReadBuffer));
        if(ret==0){
            //marks the end of file , will arise when there is no body to read
            break;
        }
        else if(ret < 0){
            perror("Error Reading From Client :");
            ResponseCode = 400; //bad request
            return;
        }
        else{
            RequestString.append(ReadBuffer,ret);
        }
    }
}

void http_handler::PrintClientRequestString(){
    std::cout<<RequestString<<"\n";
}