cmake_minimum_required(VERSION 3.20)

project(http_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(http_server
	src/main.cpp
	src/server.cpp
	src/connection.cpp
	src/http_parser.cpp
	src/http_request.cpp
	src/http_response.cpp
	src/router.cpp
	src/server.cpp
)

target_include_directories(http_server PRIVATE include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_MODE)
endif()
