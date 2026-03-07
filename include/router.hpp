//router.hpp
//will support :
//  static routes
//  dynamic routes
//methods stored in : std::map<pair<method,path>,handler>

#pragma once
#include <map>
#include <functional>
#include <string>
#include <http_request.hpp>
#include <http_response.hpp>

using Handler = std::function<HttpResponse(const HttpRequest&)>;

class Router {
    private:
        std::map<std::pair<HttpMethod,std::string>, Handler> routes;
        
    public:
        void add(HttpMethod method, const std::string& path, Handler handler);
        HttpResponse route(const HttpRequest& request);
};