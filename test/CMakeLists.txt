cmake_minimum_required(VERSION 3.28)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER /usr/bin/gcc)

enable_testing()

project(EventShareOS_Testing)

add_subdirectory("../EventShareOS"  binary_dir )
add_subdirectory("Unity" )

include_directories(../EventShareOS)
include_directories(./Unity)

# Versioning Test
add_executable(TestAppVersion "./tests/test_versioning.c")

add_test(NAME app_versioning COMMAND TestAppVersion)

target_link_libraries(TestAppVersion PUBLIC EventShareOS)
target_link_libraries(TestAppVersion PUBLIC Unity)



