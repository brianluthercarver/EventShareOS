/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************

File: posix_timer.c
In linux, time is retrieved by the clock_gettime() function. 
This function offers the higher nanosecond resolution for
precision. In this case we will be using the microsecond time
to generate millisecond events.

For polling linux systems use poll_time_keeper().

************************************************************/

#include <time.h>
#include <stdint.h>
#include <stdio.h>

#include "soft_timer.h"

#define ONE_MILLISECOND_IN_NANO   10000
#define CONVERT_SECOND_TO_NANO    1000000000


static uint64_t nanosecond_time = 0;
static uint64_t nanosecond_next_time_count = 0;

// Function: init_poll_time_keeper
// Initializes the posix time polling keeper

void init_poll_time_keeper() {

    struct timespec current_time;

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    nanosecond_time = current_time.tv_sec * CONVERT_SECOND_TO_NANO +
                      (uint64_t) current_time.tv_nsec;

    // timer has not been initialized 
    if (nanosecond_next_time_count == 0) {
        nanosecond_next_time_count = nanosecond_time + ONE_MILLISECOND_IN_NANO;
    }  
}


// Function: poll_time_keeper()
// For polling linux systems, updates the time_keeper

void poll_time_keeper() {

    struct timespec current_time;

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    nanosecond_time = current_time.tv_sec * CONVERT_SECOND_TO_NANO +
                      (uint64_t) current_time.tv_nsec;         

    // check to run polling
    if (nanosecond_time > nanosecond_next_time_count) {
        time_keeper();
        nanosecond_next_time_count = nanosecond_time + ONE_MILLISECOND_IN_NANO;
    }
}

