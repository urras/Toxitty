project(Toxitty)

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++0x -O0 -ggdb")
set(src src/main.cpp src/buffers.cpp src/callbacks.cpp src/commands.cpp src/interface.cpp src/keyhandler.cpp)
set(libs "-lncursesw")

add_executable(toxitty ${src})
target_link_libraries(toxitty ${libs})
