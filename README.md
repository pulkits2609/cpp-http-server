# C++ HTTP/1.1 Server (From Scratch)

A lightweight **HTTP/1.1 server implemented completely from scratch in C++**, built as a **systems programming portfolio project** to explore low-level networking, protocol parsing, and server architecture design.

The purpose of this project is to understand **how real web servers work internally** by implementing the core components manually rather than relying on existing frameworks or libraries.

The architecture and design approach take inspiration from well-known servers such as:

- **nginx**
- **Node.js HTTP core**
- lightweight C++ frameworks like **Crow** and **Pistache**

---

# Project Goals

The goal of this project is to build a **production-style HTTP server step-by-step** while demonstrating knowledge of:

- Linux socket programming
- TCP networking fundamentals
- HTTP/1.1 protocol parsing
- clean server architecture design
- request / response lifecycle management
- modular C++ systems programming

The project is being developed incrementally so that each stage demonstrates a deeper understanding of **network servers and backend infrastructure systems**.

---

# Current Features

## Networking

- TCP socket server using Linux socket APIs
- manual socket creation using `socket()`
- server binding using `bind()`
- listening for incoming connections using `listen()`
- client acceptance loop using `accept()`

The server currently handles connections sequentially and passes accepted client sockets into a **connection lifecycle handler**.

---

## HTTP Request Parsing

The server reads raw HTTP request data directly from the TCP socket and parses it into a structured `HttpRequest` object.

Supported parsing features:

- HTTP request line parsing (`METHOD PATH VERSION`)
- strict request line validation
- header parsing into `std::unordered_map`
- automatic detection of `Content-Length`
- request body reading based on content length
- support for custom HTTP headers
- malformed request detection and rejection
- HTTP/1.1 `Host` header validation

Example internal request representation:

```cpp
HttpMethod method;
std::string path;
std::string version;
std::unordered_map<std::string,std::string> headers;
std::string body;
```
---

## HTTP Response Builder

Responses are generated through a structured `HttpResponse` class.

Features:

- HTTP status code handling
- status text generation
- header management
- automatic `Content-Length`
- response serialization

Example generated response:

```cpp
HTTP/1.1 200 OK
Content-Type: text/plain
Content-Length: 5
Connection: close
Hello
```

---

## Router System

A simple router maps `(method, path)` pairs to handler functions.

Example route:

```cpp
router.add(HttpMethod::GET, "/", [](const HttpRequest& req){
    HttpResponse res;
    res.setStatus(HttpStatus::OK);
    res.setBody("Hello from Router");
    return res;
});
```

If no route is found the server returns:

```cpp
HTTP/1.1 404 Not Found
```


This project is being developed incrementally to demonstrate understanding of **low-level networking, HTTP protocol mechanics, and scalable server architecture design**.

# Author

**Pulkit Sharma**

Systems Programming & Backend Development Enthusiast  
Focused on low-level networking, scalable server architecture, and building software from first principles.