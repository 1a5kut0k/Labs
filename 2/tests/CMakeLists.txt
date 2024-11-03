find_package(Catch2 3 REQUIRED)

add_executable(test tests.cpp)

target_link_libraries(test point polyhedron Catch2::Catch2WithMain)