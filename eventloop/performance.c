
/************************************************************

File: performance.h

Description:  The performance monitor captures the total
time and run occurrence for system overhead and for each
module.  The performance statistics array captures the 
total time running in miliseconds, total runs through the 
code, and the average run time in miliseconds. 

The array is organized as slot zero for the system overhead.
The rest of the array is sized to hold the modules. Since 
the array is allocated statically, it's up the owner of the 
customization that the array is sized sufficiently for the 
number of modules. 

For example if the modules enumeration looks like this

    MODULE_NONE, MODULE_KEYBOARD, MODULE_APP, MODULE_EOL   

Then the array should be size to 3. 

Slot Zero will be the system overhead
Slot 1 will be keyboard module
Slot 2 will be the app module. 

Time Units:
While the performance monitor is recording time in miliseconds,
we need better resolution. Miliseconds are shifted by a hundred.

For example 0.5 seconds is 500 miliseconds, it will be recorded as
50,000.  This wil yield a fractional resolution of .01 miliseconds.

Keeping track of the total time will roll over in 119.3 hours. 

************************************************************/


#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <time.h>


#include "performance.h"


#define PERFORMANCE_STATS_ARRAY_SIZE 5
#define OS_OVERHEAD_SLOT             0

typedef struct PERFORMANCE_STATS {
    uint32_t total_time;
    uint32_t total_runs;
    uint32_t average_run_time;
} performance_stats;



// variables

static uint32_t controls_size = 0;
static uint32_t modules_size  = 0;

static performance_stats stats[PERFORMANCE_STATS_ARRAY_SIZE];

static uint32_t event_queue_misses        = 0;
static uint32_t event_queue_depth_total   = 0;
static uint32_t event_queue_depth_runs    = 0;
static uint32_t event_queue_depth_average = 0;
static uint32_t current_module            = 0;

// Time keeping functions, units are 1us = 100 units
static uint32_t time_start = 0;
static uint32_t time_end = 0;
static uint32_t time_diff = 0;

// functions 

void performance_set_controls_size(uint32_t max) {
    controls_size = max;
}
void performance_set_module_size(uint32_t max) {
    modules_size = max;
}

// Function: performance_init
// The initialization of the performance section.
// The modules is listed an enum with zero and last number
// specifying the end of the list. So the performance array
// must be sized to store all the modules.

void performance_init() {
    event_queue_misses        = 0;
    event_queue_depth_total   = 0;
    event_queue_depth_runs    = 0;
    event_queue_depth_average = 0;

    memset(stats, 0, sizeof(performance_stats));

    // protections
    if (modules_size > PERFORMANCE_STATS_ARRAY_SIZE) {
        assert("Module Size must not exceed performance monitor array size.");
    }

}

#define ONE_MILLISECOND_IN_MICRO   1000
#define CONVERT_FROM_NANO_TO_MICRO 1000
#define CONVERT_FROM_MICRO_TO_MILLI 100  // shifted
#define CONVERT_SECOND_TO_MICRO    1000000

uint32_t get_posix_time() {
    struct timespec current_time;
    uint64_t microsecond_time = 0;
    uint32_t millisecond_time = 0;

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    microsecond_time = current_time.tv_sec * CONVERT_SECOND_TO_MICRO +
                       (uint64_t) current_time.tv_nsec /  CONVERT_FROM_NANO_TO_MICRO;

    millisecond_time =  (uint32_t) microsecond_time / CONVERT_FROM_MICRO_TO_MILLI;                  
    return(millisecond_time);
} 


void os_overhead_start() {

}

void modules_start() {

}

void module_begin(uint32_t module_number) {

}

/*
 
                       */