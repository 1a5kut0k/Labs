add_compile_options(--coverage)

add_link_options(--coverage)
add_library(single single_room.cpp)
target_link_libraries(single)