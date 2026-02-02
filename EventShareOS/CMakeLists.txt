# EventShareOS Library


add_library(EventShareOS
    EventShareOS.h
    #EventShare_config.h

    custom_event_loop.h
    event_data.h
    event_loop.h
    performance.h
    posix_timer.h
    soft_timer.h
    build_version.h
    event_version.h
    versioning.h

    event_data.c
    event_loop.c
    performance.c
    posix_timer.c
    soft_timer.c
    event_version.c
    versioning.c
)

target_include_directories(EventShareOS
    PUBLIC
    ${CMAKE_CURRENT_SOURCE}
)

