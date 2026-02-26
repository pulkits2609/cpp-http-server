cmake_minimum_required(VERSION 3.16)

project(cpp_http_server VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp-http-server
    src/main.cpp
)

target_include_directories(cpp-http-server PRIVATE include)
