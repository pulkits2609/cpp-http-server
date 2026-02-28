cmake_minimum_required(VERSION 3.20)

project(http_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(http_server
	src/main.cpp
	src/tcp_socket.cpp
	src/http_handler.cpp
)

target_include_directories(http_server PRIVATE include)
