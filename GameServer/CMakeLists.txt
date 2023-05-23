cmake_minimum_required(VERSION 3.25)
project(GameServer VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BUILD_RPATH}")

add_executable(GameServer gameserver.cpp)

target_include_directories(GameServer PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/Resources"
        "${PROJECT_SOURCE_DIR}/Protocol")

set_target_properties(GameServer PROPERTIES LINKER_LANGUAGE CXX)

# Allows Linking with Library Generated for SharedResources. Currently useless as all template definitions are in inline header files
add_subdirectory(Resources)
add_subdirectory(Protocol)
target_link_libraries(GameServer PUBLIC Protocol)
target_link_libraries(GameServer PUBLIC Resources)