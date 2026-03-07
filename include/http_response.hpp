//http_response.hpp
//handles :
//  status codes
//  status text
//  headers
//  body
//  returning full response string (function)

#pragma once
#include<iostream>
#include<string>
#include<unordered_map>

enum class HttpStatus {
    OK = 200, 
    CREATED = 201, 
    NO_CONTENT = 204, 
    BAD_REQUEST = 400, 
    FORBIDDEN = 403,
    NOT_FOUND = 404, 
    METHOD_NOT_ALLOWED = 405, 
    INTERNAL_SERVER_ERROR = 500
};

class HttpResponse{
    private:
    size_t statusCode{};
    std::string statusText{};
    std::unordered_map<std::string, std::string> headers;
    std::string body{};
    
    public:
    void clearValues();
    void setStatus(HttpStatus status);
    void setHeader(std::string key, std::string value);
    void setBody(std::string body);

    std::string buildResponse();
};