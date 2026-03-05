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
add_executable(TestDataQueue "./tests/test_data_queue.c" "./tests/test_event_base.c") 

add_test(NAME test_data_queue COMMAND TestDataQueue)

target_link_libraries(TestDataQueue PUBLIC EventShareOS)
target_link_libraries(TestDataQueue PUBLIC Unity)

target_include_directories(TestDataQueue
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}../EventShareOS
    ${CMAKE_CURRENT_SOURCE_DIR}./Unity
)

# Versioning Test
add_executable(TestAppVersion "./tests/test_versioning.c" "./tests/test_event_base.c")

add_test(NAME test_app_versioning COMMAND TestAppVersion)

target_link_libraries(TestAppVersion PUBLIC EventShareOS)
target_link_libraries(TestAppVersion PUBLIC Unity)

target_include_directories(TestAppVersion
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}../EventShareOS
    ${CMAKE_CURRENT_SOURCE_DIR}./Unity
)


# EventShare Core Test
add_executable(TestEventCore "./tests/test_event_core.c" "./tests/test_event_base.c")

add_test(NAME test_event_core COMMAND TestEventCore)

target_link_libraries(TestEventCore PUBLIC EventShareOS)
target_link_libraries(TestEventCore PUBLIC Unity)

target_include_directories(TestEventCore
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}../EventShareOS
    ${CMAKE_CURRENT_SOURCE_DIR}./Unity
)

# EventShare Soft Timers Test
add_executable(TestSoftTimers "./tests/test_soft_timer.c" "./tests/test_event_base.c")

add_test(NAME test_soft_timer COMMAND TestSoftTimers)

target_link_libraries(TestSoftTimers PUBLIC EventShareOS)
target_link_libraries(TestSoftTimers PUBLIC Unity)

target_include_directories(TestSoftTimers
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}../EventShareOS
    ${CMAKE_CURRENT_SOURCE_DIR}./Unity
)