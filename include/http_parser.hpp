//http_parser.hpp
//handles : 
//  parsing request line
//  parsing headers into map
//  parse body
//  detection of malformed / wrong requests

#include<iostream>
#include<vector>
#include<unordered_map>

enum class ParseResult{
    OK,
    BAD_REQUEST,
    INCOMPLETE
};

class HttpParser{
    private:

    public:
    void clearValues();
    std::vector<std::string> parseStatusLine(const std::string& requestString);
    ParseResult parseHeaders(const std::string& requestString, std::unordered_map<std::string, std::string>& headerMap);
    size_t parseContentLength(const std::unordered_map<std::string,std::string>& headers);
};