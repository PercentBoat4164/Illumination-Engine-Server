add_executable(GameServer gameserver.cpp)

set_target_properties(GameServer PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(Resources)
add_subdirectory(Protocol)

target_include_directories(GameServer PUBLIC "Resources" "Protocol")

target_link_libraries(GameServer PUBLIC Resources Protocol)