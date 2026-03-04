//http_request.hpp
//stores : 
//  method called
//  path
//  version
//  headers (unordered_map)
//  body

#include<iostream>
#include<string>
class HttpRequest{
    private:
    std::string statusLine{};
    std::string headers{};
    std::string body{};

    public:
    void clearValues();
    void setStatusLine(const std::string status);
    void setHeaders(const std::string head);
    void printRequestData();
    void setBody(const std::string bodyData);
};