//http_handler.hpp
//protocol logic handling
#pragma once
#include<string>

enum struct request_type : int{
    GET,
    POST,
    PUT,
    DELETE_, //DELETE_ because delete is c++ reserved word
    UNKNOWN
};

struct req_resp_handler{
    std::string RequestLine="";
    std::string RequestHeaders="";
    std::string RequestBody="";

    std::string ResponseStatusLine="";
    std::string ResponseHeaders="";
    std::string ResponseBody="";
};

class HttpHandler{
    private:
    std::string RequestString="";
    int SessionFD=-1;
    int ResponseCode=0;
    
    req_resp_handler req_resp_handle;
    request_type req_type; 

    public:
    void getSessionFD(int SesFD);
    
    void readClientRequest();

    size_t parseContentLength(); //for Reading Body of Request

    std::string sendClientResponse();

    void printClientRequestString();

};



