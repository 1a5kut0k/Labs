add_compile_options(--coverage)

add_link_options(--coverage)

add_library(lux lux_room.cpp)
target_link_libraries(lux fmt::fmt)