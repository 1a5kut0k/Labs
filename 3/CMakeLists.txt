cmake_minimum_required(VERSION 3.16)
project(oopprog3)

add_compile_options(--coverage)

add_link_options(--coverage)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(src)
add_subdirectory(tests)
