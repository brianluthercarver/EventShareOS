# EventShareOS Library


add_library(Unity
    unity.h
    unity.c
)

target_include_directories(Unity
    PUBLIC
    ${CMAKE_CURRENT_SOURCE}
)

