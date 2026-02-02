cmake_minimum_required(VERSION 3.28)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER /usr/bin/gcc)

add_compile_options(-Wall -Wextra -g)

enable_testing()

project(EventShareOS_Testing)

add_subdirectory("../EventShareOS"  binary_dir )
add_subdirectory("Unity" )

include_directories(../EventShareOS)
include_directories(./Unity)

# Event Data Test
add_executable(TestDataQueue "./tests/test_data_queue.c" ./tests/test_eventloop.c) 

add_test(NAME test_data_queue COMMAND TestDataQueue)

target_link_libraries(TestDataQueue PUBLIC EventShareOS)
target_link_libraries(TestDataQueue PUBLIC Unity)

# Versioning Test
add_executable(TestAppVersion "./tests/test_versioning.c")

add_test(NAME test_app_versioning COMMAND TestAppVersion)

target_link_libraries(TestAppVersion PUBLIC EventShareOS)
target_link_libraries(TestAppVersion PUBLIC Unity)



