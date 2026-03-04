#include<iostream>
#include<http_request.hpp>

#ifdef DEBUG_MODE
    #define DEBUG_LOG(x) std::cout<<x<<"\n";
#else
    #define DEBUG_LOG(x)
#endif

void HttpRequest::clearValues(){
    headers = "";
    statusLine = "";
}

void HttpRequest::setHeaders(const std::string head){
    headers = head;
}

void HttpRequest::setStatusLine(const std::string status){
    statusLine = status;
}

void HttpRequest::setBody(const std::string bodyData){
    body = bodyData;
}

void HttpRequest::printRequestData(){
    DEBUG_LOG("Client Status Line : ")
    DEBUG_LOG(statusLine)
    DEBUG_LOG("\nClient Headers : ")
    DEBUG_LOG(headers)
    DEBUG_LOG("\nClient Body : ")
    DEBUG_LOG(body)
}