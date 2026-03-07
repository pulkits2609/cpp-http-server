//http_request.hpp
//stores : 
//  method called
//  path
//  version
//  headers (unordered_map)
//  body

#pragma once
#include<iostream>
#include<http_method.hpp>
#include<unordered_map>
#include<string>
class HttpRequest{
    private:
    HttpMethod method{};
    std::string path{};
    std::string version{};
    std::unordered_map<std::string,std::string> headers;
    std::string body{};

    public:
    void clearValues();
    void setStatusLine(HttpMethod method_http, std::string path_http, std::string version_http);
    void setHeaders(const std::unordered_map<std::string,std::string> head_mp);
    void printRequestValues();
    void setBody(const std::string bodyData);
    HttpMethod getMethod() const;
    std::string getPath() const;
};