project(Toxitty)

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11")
set(src "src/main.cpp")
set(libs "-lncursesw")

add_executable(toxitty ${src})
target_link_libraries(toxitty ${libs})
