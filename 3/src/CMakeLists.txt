add_executable(main main.cpp)

add_subdirectory(application)
add_subdirectory(classes)
add_subdirectory(interface)
find_package(Threads REQUIRED)


target_link_libraries(main app interface lux single multiple fmt::fmt Threads::Threads)