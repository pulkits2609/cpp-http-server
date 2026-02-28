//http_handler.hpp
//protocol logic handling
#pragma once
#include<string>

class http_handler{
    private:
    std::string RequestString="";
    int SessionFD=-1;
    int ResponseCode=0; 

    public:
    void GetSessionFD(int SesFD);
    
    void ReadClientRequest();

    void PrintClientRequestString();

};