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
    size_t header_end = RequestString.find("\r\n\r\n");
    RequestHeader = RequestString.substr(0, header_end);
    RequestBody = RequestString.substr(header_end + 4);

    //Parse Content-Length
    size_t content_length = ParseContentLength();

    // Reading remaining body if incomplete
    while (RequestBody.size() < content_length) {
        int ret = read(SessionFD, ReadBuffer, sizeof(ReadBuffer));
        if (ret <= 0) {
            perror("Error Reading Body:");
            return;
        }
        RequestBody.append(ReadBuffer, ret);
    }
}

size_t http_handler::ParseContentLength(){
    size_t pos = RequestHeader.find("Content-Length:");

    if(pos == std::string::npos) return 0; //no body is there

    size_t value_start = pos + 15; // length of "Content-Length:"
    while (RequestHeader[value_start] == ' ')
        value_start++;

    size_t value_end = RequestHeader.find("\r\n", value_start);

    std::string length_str =
        RequestHeader.substr(value_start, value_end - value_start);

    return std::stoul(length_str);


}

std::string http_handler::SendClientResponse(){
    std::string Response = //creating basic minimal response
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 5\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Hello";
    return Response;
}

//DEBUGGING FUNCTION
void http_handler::PrintClientRequestString(){
    std::cout<<"Client Request header : \n";
    std::cout<<RequestHeader<<"\n";
    std::cout<<"Client Request Body :\n";
    std::cout<<RequestBody<<"\n";
}