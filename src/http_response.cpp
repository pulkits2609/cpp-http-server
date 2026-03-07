#include<iostream>
#include<http_response.hpp>

void HttpResponse::clearValues(){
    statusCode = 0;
    statusText.clear();
    headers.clear();
    body.clear();
}

void HttpResponse::setStatus(HttpStatus status){

    statusCode = static_cast<size_t>(status);

    switch(status){
        case HttpStatus::OK:
            statusText = "OK";
            break;

        case HttpStatus::CREATED:
            statusText = "Created";
            break;

        case HttpStatus::NO_CONTENT:
            statusText = "No Content";
            break;

        case HttpStatus::BAD_REQUEST:
            statusText = "Bad Request";
            break;

        case HttpStatus::NOT_FOUND:
            statusText = "Not Found";
            break;

        case HttpStatus::METHOD_NOT_ALLOWED:
            statusText = "Method Not Allowed";
            break;

        case HttpStatus::INTERNAL_SERVER_ERROR:
            statusText = "Internal Server Error";
            break;

        case HttpStatus::FORBIDDEN:
            statusText = "Forbidden";
            break;

        default:
            statusText = "Internal Server Error";
            statusCode = 500;
            break;
    }
}

void HttpResponse::setHeader(std::string key, std::string value){
    headers[key]=value;
}

void HttpResponse::setBody(std::string bodyData){
    body = bodyData;
    headers["Content-Length"] = std::to_string(body.size());
}

std::string HttpResponse::buildResponse(){
    std::string response{};
    response.reserve(256 + body.size()); //to avoid repeated reallocations , can hamper performance
    
    response+="HTTP/1.1 ";
    response+=std::to_string(statusCode);
    response+=" ";
    response+=statusText;
    response+="\r\n";

    if(headers.find("Connection") == headers.end()){
        headers["Connection"] = "close";
    }

    auto it = headers.begin();
    while(it!=headers.end()){
        response.append(it->first);
        response.append(": ");
        response.append(it->second);
        response.append("\r\n");
        it++;
    }

    response+="\r\n";
    response+=body;

    return response;
}