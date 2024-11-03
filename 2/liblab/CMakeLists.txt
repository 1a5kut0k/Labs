add_compile_options(--coverage)

add_link_options(--coverage)
add_library(point point.h point.cpp)
add_library(polyhedron polyhedron.h polyhedron.cpp point.cpp)