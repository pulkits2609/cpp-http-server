#include<iostream>
#include<string>
#include<http_parser.hpp>
#include<algorithm>

ParseResult HttpParser::parseHeaders(const std::string& requestString,
std::unordered_map<std::string, std::string>& headerMap)
{
    size_t headerStart = requestString.find("\r\n"); // end of request line
    if(headerStart == std::string::npos){
        return ParseResult::BAD_REQUEST;
    }

    size_t headerEnd = requestString.find("\r\n\r\n"); // end of headers
    if(headerEnd == std::string::npos){
        return ParseResult::BAD_REQUEST;
    }

    std::string headerString = requestString.substr(headerStart + 2, headerEnd - (headerStart + 2));

    headerStart = 0;
    headerEnd = headerString.find("\r\n");

    while(headerEnd != std::string::npos)
    {
        size_t colon = headerString.find(":", headerStart);

        if(colon == std::string::npos || colon > headerEnd){
            return ParseResult::BAD_REQUEST;
        }

        std::string key = headerString.substr(headerStart, colon - headerStart);
        std::transform(key.begin(),key.end(),key.begin(),::tolower);
        std::string value = headerString.substr(colon + 1, headerEnd - (colon + 1));

        // trim leading spaces from value
        while(!value.empty() && value.front() == ' '){
            value.erase(value.begin());
        }

        // trim trailing spaces from value
        while(!value.empty() && value.back() == ' '){
            value.pop_back();
        }
        
        //trim keys 
        while(!key.empty()&& key.back()==' '){
            key.pop_back();
        }

        headerMap[key] = value;

        headerStart = headerEnd + 2;
        headerEnd = headerString.find("\r\n", headerStart);
    }

    // handle last header line (no trailing CRLF inside substring)
    if(headerStart < headerString.size())
    {
        size_t colon = headerString.find(":", headerStart);

        if(colon == std::string::npos){
            return ParseResult::BAD_REQUEST;
        }

        std::string key = headerString.substr(headerStart, colon - headerStart);
        std::transform(key.begin(),key.end(),key.begin(),::tolower);
        std::string value = headerString.substr(colon + 1);

        //trim value
        while(!value.empty() && value.front() == ' '){
            value.erase(value.begin());
        }

        while(!value.empty() && value.back() == ' '){
            value.pop_back();
        }

        //trim keys 
        while(!key.empty()&& key.back()==' '){
            key.pop_back();
        }

        headerMap[key] = value;
    }

    if(headerMap.find("host")==headerMap.end()){
        return ParseResult::BAD_REQUEST;
    }

    return ParseResult::OK;
}

size_t HttpParser::parseContentLength(const std::unordered_map<std::string,std::string>& headers)
{
    auto it = headers.find("content-length");

    if(it == headers.end())
        return 0;

    try{
        return std::stoul(it->second);
    }
    catch(...){
        return 0;
    }
}

std::vector<std::string> HttpParser::parseStatusLine(const std::string& requestString)
{
    std::vector<std::string> tokens; //returns method , path and version in status line of requestString

    size_t lineEnd= requestString.find("\r\n");

    if(lineEnd == std::string::npos){
        return tokens; //return empty vector because bad request
    }

    std::string statusLine= requestString.substr(0, lineEnd);

    size_t firstSpace= statusLine.find(' ');
    size_t secondSpace= statusLine.find(' ', firstSpace + 1);

    if(firstSpace == std::string::npos || secondSpace == std::string::npos){
        return tokens; //bad request
    }

    std::string method= statusLine.substr(0, firstSpace);
    std::string path= statusLine.substr(firstSpace + 1, secondSpace - firstSpace - 1);
    std::string version= statusLine.substr(secondSpace + 1);

    // ensure no extra spaces
    if(version.find(' ') != std::string::npos){
        return tokens;
    }

    // method validation
    if(method != "GET" && method != "POST" && method != "PUT" && method != "DELETE"){
        return tokens;
    }

    // path validation
    if(path.empty() || path[0] != '/'){
        return tokens;
    }

    // HTTP version validation
    if(version.size() < 6){
        return tokens;
    }

    if(version.substr(0,5) != "HTTP/"){
        return tokens;
    }

    tokens.push_back(method);
    tokens.push_back(path);
    tokens.push_back(version);

    return tokens;
}

void HttpParser::clearValues(){
    
}