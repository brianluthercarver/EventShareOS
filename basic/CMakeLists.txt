cmake_minimum_required(VERSION 3.28)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER /usr/bin/gcc)

project(Basic_Example)

add_subdirectory("../EventShareOS" binary_dir)

add_executable(basic_main "basic_main.c")

include_directories(basic ../EventShareOS)
target_link_libraries(basic_main PUBLIC EventShareOS)

target_sources(basic_main PRIVATE
    basic_eventloop.c
    keyboard_module.c
    app_module.c
    quote_module.c
)

