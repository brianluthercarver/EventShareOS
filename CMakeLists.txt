cmake_minimum_required(VERSION 3.28)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER /usr/bin/gcc)

project(EventShareOS)

add_executable(basic_main "./basic/basic_main.c")

include_directories(eventloop basic)

target_sources(basic_main PRIVATE
    ./basic/basic_eventloop.c
    ./basic/keyboard_module.c
    ./basic/app_module.c
    
    ./eventloop/event_loop.c
    ./eventloop/soft_timer.c
    ./eventloop/posix_timer.c
    ./eventloop/performance.c
    ./eventloop/event_data.c
)

