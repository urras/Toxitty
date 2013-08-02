cmake_minimum_required(VERSION 2.8)
project(Toxitty)

# Include our CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

# Find JsonCpp
find_package(JsonCpp REQUIRED)
include_directories(${JsonCpp_INCLUDE_DIRS})
link_libraries(${JsonCpp_LIBRARIES})

set(src src/main.cpp src/buffers.cpp src/callbacks.cpp src/commands.cpp src/config.cpp src/core.cpp src/interface.cpp src/input.cpp src/keyhandler.cpp src/misc.cpp)
set(src_tox tox/core/DHT.c tox/core/friend_requests.c tox/core/LAN_discovery.c tox/core/Lossless_UDP.c tox/core/Messenger.c tox/core/net_crypto.c tox/core/network.c)
set(libs "-lncurses -lsodium -lboost_system -lboost_thread")

add_executable(toxitty ${src} ${src_tox})
target_link_libraries(toxitty ${libs})
