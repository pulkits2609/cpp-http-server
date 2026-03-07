#include <router.hpp>

void Router::add(HttpMethod method, const std::string& path, Handler handler){
    routes[{method, path}] = handler;
}

HttpResponse Router::route(const HttpRequest& request){
    auto it = routes.find({request.getMethod(), request.getPath()});
    if(it != routes.end()){
        return it->second(request);
    }

    HttpResponse res;
    res.setStatus(HttpStatus::NOT_FOUND);
    res.setHeader("Content-Type","text/plain");
    res.setBody("Not Found");

    return res;
}