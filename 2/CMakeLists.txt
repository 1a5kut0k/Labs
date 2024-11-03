cmake_minimum_required(VERSION 3.16)
# название проекта (обязательно)
project(oopprog2)

add_compile_options(--coverage)

add_link_options(--coverage)

# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 20)
# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
add_subdirectory(liblab)
# добавление подпроекта с тестами
add_subdirectory(tests)
# создание исполняемого файла для диалоговой программы
