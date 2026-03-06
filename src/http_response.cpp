#include<iostream>
#include<http_response.hpp>

void HttpResponse::clearValues(){
    
}

std::string HttpResponse::badRequestResponse(){
    std::string response=
    "HTTP/1.1 400 Bad Request\r\n"
    "Content-Type: text/plain\r\n"
    "Content-Length: 11\r\n"
    "Connection: close\r\n"
    "\r\n"
    "Bad Request";
    return response;
}

std::string HttpResponse::forbiddenRequestResponse(){
    std::string response =
    "HTTP/1.1 403 Forbidden\r\n"
    "Content-Type: text/plain\r\n"
    "Content-Length: 9\r\n"
    "Connection: close\r\n"
    "\r\n"
    "Forbidden";

    return response;
}

std::string HttpResponse::defaultRequestResponse(){
    
}