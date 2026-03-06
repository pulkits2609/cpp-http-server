//connection.cpp

#include<connection.hpp>
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<string>

#ifdef DEBUG_MODE
    #define DEBUG_LOG(x) std::cout<<x<<"\n";
#else
    #define DEBUG_LOG(x)
#endif

bool ClientConnection::getClientSession(int session){

    if(session < 0){
        DEBUG_LOG("\nInvalid Session\n")
        return false;
    }
    
    sessionfd = session;
    return true;
}

void ClientConnection::getClientAddress(const sockaddr_in cliAddr){
    clientAddress = cliAddr;
}

void ClientConnection::clearValues(){

    memset(&clientAddress,0,sizeof(clientAddress));
    
    parser.clearValues();
    request.clearValues();
    response.clearValues();
    requestString = "";
}

bool ClientConnection::readClientRequest(){
    clearValues();
    //this reads until CRLF CRLF Delimeter is found
    while (requestString.find("\r\n\r\n") == std::string::npos){
        memset(readBuffer,0,sizeof(readBuffer)); //clear read buffer before storing again 
        int ret = read(sessionfd,readBuffer,sizeof(readBuffer));
        if(ret==0){
            //marks the end of file , will arise when there is nothing to read , not very likely to happen because its only sent when client breaks connection
            DEBUG_LOG("Client Closed Connection Unexpectedly")
            return false;
        }
        else if(ret < 0){
            perror("Error Reading From Client :");
            return false;
        }
        else{
            requestString.append(readBuffer,ret); //append read data to RequestString
        }
    }
    return true;
}

void ClientConnection::closeClientConnection(){
    close(sessionfd);
    sessionfd = -1;
}

void ClientConnection::printClientAddress(){
    DEBUG_LOG("CLIENT ADDRESS : "<<inet_ntoa(clientAddress.sin_addr)<<":"<<ntohs(clientAddress.sin_port))
}

void ClientConnection::handleClient(){

    printClientAddress();

    if(!readClientRequest()){
        DEBUG_LOG("Bad Request From Client")
        std::string resp = response.badRequestResponse();
        write(sessionfd, resp.c_str(), resp.size()); 
        closeClientConnection();
        return;
    }

    auto tokens = parser.parseStatusLine(requestString);
    if(tokens.empty()){
        DEBUG_LOG("Invalid Request Line")
        std::string resp = response.badRequestResponse();
        write(sessionfd, resp.c_str(), resp.size()); 
        closeClientConnection();
        return;
    }

    HttpMethod method;
    if(tokens[0] == "GET") method = HttpMethod::GET;
    else if(tokens[0] == "POST") method = HttpMethod::POST;
    else if(tokens[0] == "PUT") method = HttpMethod::PUT;
    else if(tokens[0] == "DELETE") method = HttpMethod::DELETE_;
    else{
        DEBUG_LOG("UNKNOWN METHOD , BAD REQUEST") //not very likely to come because we have prior checks
        std::string resp = response.badRequestResponse();
        write(sessionfd, resp.c_str(), resp.size()); 
        closeClientConnection();
        return;
    }

    request.setStatusLine(method, tokens[1], tokens[2]);    

    std::unordered_map<std::string,std::string> headers;

    ParseResult result = parser.parseHeaders(requestString, headers);

    if(result != ParseResult::OK){
        DEBUG_LOG("Malformed Headers")
        std::string resp = response.badRequestResponse();
        write(sessionfd, resp.c_str(), resp.size()); 
        closeClientConnection();
        return;
    }

    request.setHeaders(headers);

    size_t headerEnd = requestString.find("\r\n\r\n");

    if(!(method == HttpMethod::GET)){ //only read content length and body if method is not GET
        std::string bodyPart = requestString.substr(headerEnd + 4);

        size_t contentLength = parser.parseContentLength(headers);
        if(contentLength > MAX_BODY_SIZE){
            DEBUG_LOG("BODY LIMIT REACHED")
            std::string resp = response.forbiddenRequestResponse();
            write(sessionfd, resp.c_str(), resp.size());             
            closeClientConnection();
            return;
        }

        if(bodyPart.size() < contentLength){

            while(bodyPart.size() < contentLength){

                int ret = read(sessionfd, readBuffer, sizeof(readBuffer));

                if(ret <= 0)
                    break;

                bodyPart.append(readBuffer, ret);
            }
        }

        request.setBody(bodyPart);
    }

    // SEND BASIC RESPONSE
    std::string resp = response.defaultRequestResponse();

    write(sessionfd, resp.c_str(), resp.size());    

    request.printRequestValues();

    closeClientConnection();
}


