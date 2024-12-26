add_compile_options(--coverage)

add_link_options(--coverage)
add_library(multiple multiple_room.cpp)
target_link_libraries(multiple)