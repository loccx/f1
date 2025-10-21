cmake_minimum_required(VERSION 4.1.2)
project(F1)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML REQUIRED COMPONENTS Graphics Window System)

add_executable(main main.cpp map.cpp input.cpp physics.cpp render.cpp utils/collision.cpp)

target_link_libraries(main PRIVATE SFML::Graphics SFML::Window SFML::System)
