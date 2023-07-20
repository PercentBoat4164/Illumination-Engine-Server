include(FindProtobuf)

add_library(Protocol PacketReader.cpp)

add_subdirectory(PacketORM)

target_include_directories(Protocol PUBLIC ../Resources)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Protobuf_INCLUDE_DIRS})
target_link_libraries(Protocol PacketORM  ${Protobuf_LIBRARIES})