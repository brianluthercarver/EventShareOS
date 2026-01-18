# EventShareOS Library

set(EVENTSHAREOS_VERSION "0.1.0")

#set_target_properties(EventShareOS PROPERTIES
#    VERSION ${EVENTSHAREOS_VERSION}
#    SOVERSION 2
#    )

add_library(EventShareOS
    EventShareOS.h
    custom_event_loop.h
    event_data.h
    event_loop.h
    performance.h
    posix_timer.h
    soft_timer.h
    version.h
    event_data.c
    event_loop.c
    performance.c
    posix_timer.c
    soft_timer.c
    )

target_include_directories(EventShareOS
    PUBLIC
    ${CMAKE_CURRENT_SOURCE}
    )

