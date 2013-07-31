project(Toxitty)

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

set(src src/main.cpp src/buffers.cpp src/callbacks.cpp src/commands.cpp src/config.cpp src/interface.cpp src/input.cpp src/keyhandler.cpp src/misc.cpp)
set(src_tox tox/core/DHT.c tox/core/friend_requests.c tox/core/LAN_discovery.c tox/core/Lossless_UDP.c tox/core/Messenger.c tox/core/net_crypto.c tox/core/network.c)
set(libs "-lncurses -lsodium -ljsoncpp")

add_executable(toxitty ${src} ${src_tox})
target_link_libraries(toxitty ${libs})
