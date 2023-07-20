include(FindProtobuf)

include_directories(${PROTOBUF_INCLUDE_DIR})
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER Base.proto)

add_library(PacketORM ${PROTO_HEADER} ${PROTO_SRC})