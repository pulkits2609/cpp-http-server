//http_request.cpp

#include<iostream>
#include<http_request.hpp>

#ifdef DEBUG_MODE
    #define DEBUG_LOG(x) std::cout<<x<<"\n";
#else
    #define DEBUG_LOG(x)
#endif

void HttpRequest::clearValues(){
    method= HttpMethod::UNKNOWN;
    path="";
    version="";
    headers.empty();
    body="";
}

void HttpRequest::setHeaders(std::unordered_map<std::string,std::string> head_mp){
    headers = head_mp;
}

void HttpRequest::setStatusLine(HttpMethod method_http, std::string path_http, std::string version_http){
    method = method_http;
    path = path_http;
    version = version_http;
}

void HttpRequest::setBody(const std::string bodyData){
    body = bodyData;
}

void HttpRequest::printRequestValues(){

    DEBUG_LOG("=========== HTTP REQUEST ===========")

    // METHOD
    std::string methodStr;
    switch(method){
        case HttpMethod::GET: methodStr= "GET"; break;
        case HttpMethod::POST: methodStr= "POST"; break;
        case HttpMethod::PUT: methodStr= "PUT"; break;
        case HttpMethod::DELETE_: methodStr= "DELETE"; break;
        default: methodStr = "UNKNOWN"; break;
    }
    DEBUG_LOG("Method  : " << methodStr)
    DEBUG_LOG("Path    : " << path)
    DEBUG_LOG("Version : " << version)

    DEBUG_LOG("\nHeaders:")

    //if you see this congrats you just got rick rolled 🕺 

    for(const auto& [key,value] : headers){
        DEBUG_LOG(key << " : " << value)
    }

    DEBUG_LOG("\nBody:")
    DEBUG_LOG(body)

    DEBUG_LOG("====================================")
}