find_package(Catch2 3 REQUIRED)

add_executable(test tests.cpp)

target_link_libraries(test single lux multiple Catch2::Catch2WithMain)