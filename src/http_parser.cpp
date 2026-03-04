#include<iostream>
#include<string>
#include<http_parser.hpp>

std::string HttpParser::parseStatusLine(const std::string& requestString){
    std::string statusLine{};
    size_t lineEnd = requestString.find("\r\n");

    if(lineEnd == std::string::npos)
        return statusLine;

    statusLine = requestString.substr(0, lineEnd);

    return statusLine;
}

std::string HttpParser::parseHeaders(const std::string& requestString){
    std::string headers{};

    size_t headerStart = requestString.find("\r\n");
    if(headerStart == std::string::npos){
        return headers;
    }

    size_t headerEnd = requestString.find("\r\n\r\n");
    if(headerEnd == std::string::npos){
        return headers;
    }
    headers = requestString.substr(headerStart + 2, headerEnd - (headerStart + 2));

    return headers;
}

size_t HttpParser::parseContentLength(const std::string& headers){

    size_t pos = headers.find("Content-Length:");
    if(pos == std::string::npos)
        return 0;

    size_t value_start = pos + 15;

    while(headers[value_start] == ' ')
        value_start++;

    size_t value_end = headers.find("\r\n", value_start);

    std::string length_str =
        headers.substr(value_start, value_end - value_start);

    try{
        return std::stoul(length_str);
    }
    catch(...){
        return 0;
    }
}

void HttpParser::clearValues(){
    
}