find_package(Catch2 3 REQUIRED)

add_compile_options(--coverage)

add_link_options(--coverage)

add_executable(test test.cpp)

target_link_libraries(test lib_point lib_polyhedron Catch2::Catch2WithMain)