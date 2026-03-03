# EventShareOS Library

project(EventShareOS)



add_library(EventShareOS
    EventShareOS.h
    EventShareOS_test.h    # Used only for testing
    #EventShare_config.h
    custom_event_core.h
    posix_timer.h
    versioning.h

    inc/event_data.h

    src/event_data.c
    src/event_core.c
    src/performance.c
    src/posix_timer.c
    src/soft_timer.c
    src/event_version.c
    src/versioning.c
)

target_include_directories(EventShareOS
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    
)

