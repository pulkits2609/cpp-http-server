//connection.hpp
//this represents a client connection
//stores : 
//  sessionfd
//  readbuffer
//  writebuffer
//  request state
//  response state
//  keep-alive (yes/no) 

#include<iostream>
#include<string>
#include<arpa/inet.h>
#include<http_method.hpp>
#include<http_request.hpp>
#include<http_response.hpp>
#include<http_parser.hpp>

class ClientConnection{
    private:
    int sessionfd=-1;
    char readBuffer[512]{};
    HttpRequest request;  
    HttpResponse response;
    HttpMethod method;
    HttpParser parser;
    sockaddr_in clientAddress{};
    
    public:
    bool getClientSession(int session);
    void getClientAddress(const sockaddr_in cliAddr);
    void handleClient(); //this will be handling the whole lifecycle of request response
};
