# C++ HTTP/1.1 Server (From Scratch)

A lightweight HTTP/1.1 server built completely from scratch in C++.

I created this project to understand how real web servers actually work behind the scenes without using any frameworks or external libraries. Everything from socket handling to HTTP parsing and request routing is implemented manually.

The server follows a clean modular design where each part of the request lifecycle is handled separately (parsing, routing, response building, etc.), making it easier to understand and extend.

It supports basic HTTP methods, parsing requests into structured objects, routing them to handlers, and generating proper HTTP responses.

The design was inspired by real servers like nginx and Node.js, but the design was kept simple and focused for learning purposes.

## Project Goals
Key things this project aims to demonstrate:

- how TCP socket programming works in Linux
- how HTTP/1.1 requests are structured and parsed
- how a request moves through a server (request → processing → response)
- how to design a clean and modular server architecture
- how to handle multiple client connections using threads
- how to measure and evaluate server performance

My aim was not to create a production-ready server, but to gain a solid understanding of the fundamentals that real systems are built on.

## Features

### Networking
- TCP socket server using Linux socket APIs
- manual socket creation, bind, listen, and accept
- client connection lifecycle handling

### HTTP Parsing
- request line parsing (`METHOD PATH VERSION`)
- strict validation of method, path, and HTTP version
- header parsing into `std::unordered_map`
- case-insensitive header handling
- `Content-Length` parsing and body reading
- malformed request detection
- HTTP/1.1 `Host` header validation

### Request & Response System
- structured `HttpRequest` object
- `HttpResponse` builder with status codes and headers
- automatic `Content-Length` handling
- proper HTTP/1.1 response formatting

### Routing
- maps `(method, path)` → handler function
- lambda-based handlers
- returns `404 Not Found` for unknown routes

### Concurrency
- thread pool for handling multiple clients
- job queue using mutex and condition variable
- worker threads process requests independently

### Performance
- custom load testing tool using raw sockets
- achieves ~190K requests/sec on localhost (release build)

## Architecture Overview

The server follows a modular request handling pipeline:

```
Socket
↓
Server (accept loop)
↓
ThreadPool (job queue + worker threads)
↓
ClientConnection
↓
HttpParser
↓
HttpRequest
↓
Router
↓
Handler
↓
HttpResponse
↓
write() to socket
```


### How it works

- The server accepts incoming TCP connections
- Each connection is pushed into a thread pool queue
- Worker threads pick up connections and handle them independently
- The request is parsed into a structured `HttpRequest`
- The router decides which handler to call
- The handler generates an `HttpResponse`
- The response is serialized and sent back to the client

### Key Design Choices

- **Thread Pool Model** for concurrency instead of spawning threads per request  
- **Separation of Concerns** between parsing, routing, and response handling  
- **Stateless Connection Handling** where each request is handled independently  
- **No external libraries**, everything implemented from scratch  

## 🚀 Performance Benchmark

The server was tested using a custom load testing tool written in C++ using raw POSIX sockets and multithreading.

### [Load Testing Tool](https://github.com/pulkits2609/load-testing-tool/tree/main/http_server)

### Test Setup

- Client and server running on localhost
- Multiple worker threads generating requests
- Each request opens a TCP connection, sends an HTTP request, and reads the response
- Benchmark duration: 1 second

### Results

| Build Type | Requests/sec |
|-----------|-------------|
| Debug Build | ~35,000 req/sec |
| Release Build | ~190,000 req/sec |

### Observations

- Release builds significantly improve performance due to compiler optimizations  
- Thread pool allows multiple requests to be processed concurrently  
- Performance increases with thread count up to an optimal point  
- After a certain limit, context switching overhead reduces performance  

### Notes

- Tests are performed on localhost (no real network latency)  
- Each request uses a new TCP connection (no keep-alive)  
- Results are meant for relative comparison, not production benchmarking  

## 🛠️ Installation

### Requirements

- Linux (tested on Ubuntu)
- g++
- CMake

### Build Steps

```bash
git clone https://github.com/pulkits2609/cpp-http-server.git
cd cpp-http-server
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/http_server <IP_ADDRESS>
```
> ⚠️ **Build Type Note**
>
> - Use **Release build** for normal usage and performance testing  
> - Use **Debug build** if you want to inspect how requests are being parsed or debug issues  
>
> The Debug build includes additional logging (custom print statements) that show:
>
> - parsed request details  
> - headers and body  
> - error cases during parsing  
>
> This makes it easier to understand what is happening internally, but it also slows down performance significantly.

## Usage

Start the server:

```bash
./build/http_server <IP_ADDRESS>
```
Example:
```bash
./build/http_server 127.0.0.1
```
The server listens on port 9000.

### Test using curl
```bash
curl http://127.0.0.1:9000/
```
### Adding Routes
Routes can be defined in main.cpp:
```c++
router.add(HttpMethod::GET, "/", [](const HttpRequest& req){
    HttpResponse res;
    res.setStatus(HttpStatus::OK);
    res.setBody("Hello From Server");
    return res;
});
```

## Project Structure
```
cpp-http-server/
├── include/
│ ├── connection.hpp
│ ├── http_method.hpp
│ ├── http_parser.hpp
│ ├── http_request.hpp
│ ├── http_response.hpp
│ ├── router.hpp
│ ├── server.hpp
│ └── thread_pool.hpp
│
├── src/
│ ├── connection.cpp
│ ├── http_parser.cpp
│ ├── http_request.cpp
│ ├── http_response.cpp
│ ├── router.cpp
│ ├── server.cpp
│ ├── thread_pool.cpp
│ └── main.cpp
│
├── build/
├── CMakeLists.txt
└── README.md
```

## Design Decisions

- **Thread Pool over thread-per-connection**  
  Instead of creating a new thread for every request, a fixed number of worker threads process incoming connections. This avoids excessive thread creation overhead and scales better.

- **Separation of Concerns**  
  Parsing, routing, response building, and connection handling are split into different classes to keep the architecture clean and modular.

- **Stateless Request Handling**  
  Each connection is handled independently without shared state, reducing complexity and avoiding synchronization issues.

- **Custom HTTP Parsing**  
  Implemented request parsing manually to understand how HTTP/1.1 works internally instead of relying on libraries.

- **Synchronous I/O Model**  
  Each worker thread handles blocking I/O for simplicity and clarity, keeping the design easier to reason about.

## Limitations

- No support for HTTP keep-alive (each request creates a new connection)
- Only basic routing (no dynamic routes or middleware)
- Blocking I/O model (not using epoll or async I/O)
- Limited HTTP feature support (no chunked encoding, no advanced headers)

## Future Improvements

- Add support for static file serving
- Implement HTTP keep-alive connections
- Introduce non-blocking I/O using epoll
- Improve routing system (dynamic routes, parameters)
- Add logging system and better error handling
- Support HTTPS using OpenSSL

## Author : Pulkit Sharma
