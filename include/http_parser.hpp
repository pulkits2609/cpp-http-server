//http_parser.hpp
//handles : 
//  parsing request line
//  parsing headers into map
//  parse body
//  detection of malformed / wrong requests

#include<iostream>


class HttpParser{
    private:

    public:
    void clearValues();
    std::string parseStatusLine(const std::string& requestString);
    std::string parseHeaders(const std::string& requestString);
    size_t parseContentLength(const std::string& headers);
};