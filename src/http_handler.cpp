//HttpHandler.cpp

#include<iostream>
#include"http_handler.hpp"
#include<unistd.h>
#include<cstring>

void HttpHandler::getSessionFD(int SesFd){
    SessionFD=SesFd; //no need to check because ServerHandler will return correct FD
}

void HttpHandler::readClientRequest(){
    char ReadBuffer[512]{};

    RequestString.clear();
    req_resp_handle.RequestLine.clear();
    req_resp_handle.RequestHeaders.clear();
    req_resp_handle.RequestBody.clear();

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
    size_t req_line_end = RequestString.find("\r\n");
    if(req_line_end == std::string::npos){
        ResponseCode = 400;
        return;
    }
    req_resp_handle.RequestLine = RequestString.substr(0,req_line_end);
    req_line_end+=2;
    size_t header_end = RequestString.find("\r\n\r\n");
    if(header_end == std::string::npos){
        ResponseCode = 400;
        return;
    }
    req_resp_handle.RequestHeaders = RequestString.substr(req_line_end, header_end - req_line_end);
    req_resp_handle.RequestBody = RequestString.substr(header_end + 4);

    //Parse Content-Length
    size_t content_length = parseContentLength();

    // Reading remaining body if incomplete
    while (req_resp_handle.RequestBody.size() < content_length) {
        int ret = read(SessionFD, ReadBuffer, sizeof(ReadBuffer));
        if (ret <= 0) {
            perror("Error Reading Body:");
            return;
        }
        req_resp_handle.RequestBody.append(ReadBuffer, ret);
    }
}

size_t HttpHandler::parseContentLength(){
    size_t pos = req_resp_handle.RequestHeaders.find("Content-Length:");

    if(pos == std::string::npos) return 0; //no body is there

    size_t value_start = pos + 15; // length of "Content-Length:"
    while (req_resp_handle.RequestHeaders[value_start] == ' ')
        value_start++;

    size_t value_end = req_resp_handle.RequestHeaders.find("\r\n", value_start);

    std::string length_str =
        req_resp_handle.RequestHeaders.substr(value_start, value_end - value_start);

    return std::stoul(length_str);
}

std::string HttpHandler::sendClientResponse(){
    std::string Response = //creating basic minimal response
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 6\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Hello\n";
    return Response;
}

//DEBUGGING FUNCTION
void HttpHandler::printClientRequestString(){
    std::cout<<"Client Request header : \n";
    std::cout<<req_resp_handle.RequestHeaders<<"\n";
    std::cout<<"Client Request Body :\n";
    std::cout<<req_resp_handle.RequestBody<<"\n";
}