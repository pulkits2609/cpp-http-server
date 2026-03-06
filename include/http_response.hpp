//http_response.hpp
//handles :
//  status codes
//  status text
//  headers
//  body
//  returning full response string (function)

#include<iostream>
#include<string>
#include<unordered_map>

class HttpResponse{
    private:
    size_t statusCode{};
    std::string statusText{};
    std::unordered_map<std::string, std::string> headers;
    std::string body{};
    
    public:
    void clearValues();
    std::string badRequestResponse();
    std::string forbiddenRequestResponse();
    std::string defaultRequestResponse();
};