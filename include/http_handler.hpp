//http_handler.hpp
//protocol logic handling
#pragma once
#include<string>

class http_handler{
    private:
    std::string RequestString="";
    std::string RequestHeader="";
    std::string RequestBody="";
    int SessionFD=-1;
    int ResponseCode=0; 

    public:
    void GetSessionFD(int SesFD);
    
    void ReadClientRequest();

    size_t ParseContentLength(); //for Reading Body of Request

    std::string SendClientResponse();

    void PrintClientRequestString();

};