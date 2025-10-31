cmake_minimum_required(VERSION 3.10)
project(HTTP_SERVER_CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_executable(server src/main.cpp src/server.cpp src/request.cpp src/response.cpp src/router.cpp)
