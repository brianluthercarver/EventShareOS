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

#define ONE_MILLISECOND_IN_MICRO   1000
#define CONVERT_FROM_NANO_TO_MICRO 1000
#define CONVERT_SECOND_TO_MICRO    1000000


static uint64_t microsecond_time = 0;
static uint64_t next_time_count = 0;

// Function: init_poll_time_keeper
// Initializes the posix time polling keeper

void init_poll_time_keeper() {

    struct timespec current_time;

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    microsecond_time = current_time.tv_sec * CONVERT_SECOND_TO_MICRO +
                       (uint64_t) current_time.tv_nsec /  CONVERT_FROM_NANO_TO_MICRO;

    // timer has not been initialized 
    if (next_time_count == 0)  {
        next_time_count = microsecond_time + ONE_MILLISECOND_IN_MICRO;
    }  
}


// Function: poll_time_keeper()
// For polling linux systems, updates the time_keeper

void poll_time_keeper() {

    struct timespec current_time;

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    microsecond_time = current_time.tv_sec * CONVERT_SECOND_TO_MICRO +
                       (uint64_t) current_time.tv_nsec /  CONVERT_FROM_NANO_TO_MICRO;             

    // check to run polling
    if (microsecond_time > next_time_count) {
        time_keeper();
        next_time_count = microsecond_time + ONE_MILLISECOND_IN_MICRO;
    }
}

