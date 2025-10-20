cmake_minimum_required(VERSION 4.1.2)
project(F1)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML REQUIRED COMPONENTS Graphics Window)

add_executable(main main.cpp map.cpp)

target_link_libraries(main PRIVATE SFML::Graphics SFML::Window)
