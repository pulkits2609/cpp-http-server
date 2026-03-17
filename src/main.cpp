//main.cpp
#include<iostream>
#include<server.hpp>

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: ./http_server <IP_ADDRESS>\n";
        return -1;
    }

    Server Srv;
    if(!Srv.createSocket()){
        return -1;
    }
    if(!Srv.bindToAddress(argv[1],9000)){
        Srv.closeSocket();
        return -1;
    }
    Srv.startListening(5);

    //assign router to server
    Router& router = Srv.giveRouterInstance();
    router.add(HttpMethod::GET, "/", [](const HttpRequest& req){
        HttpResponse res;
        res.setStatus(HttpStatus::OK);
        res.setHeader("Content-Type","text/plain");
        res.setBody("Hello From Server");
        return res;
    });

    Srv.acceptLoop();
    Srv.closeSocket();

    return 0;
}