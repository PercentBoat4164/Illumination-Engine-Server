cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(IlluminationGameServer VERSION 1.0)

find_package(Protobuf REQUIRED)

add_subdirectory(src)