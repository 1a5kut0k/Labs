cmake_minimum_required(VERSION 3.16)
project(oopprog3)

add_compile_options(--coverage -std=c++2a)

add_link_options(--coverage)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(timing)
