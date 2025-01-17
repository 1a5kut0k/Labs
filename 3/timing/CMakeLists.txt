add_executable(timing timing.cpp)
find_package(Threads REQUIRED)


target_link_libraries(timing app single lux multiple Threads::Threads)