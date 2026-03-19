/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

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

#include "event_core.h"
#include "soft_timer.h"
#include "performance.h"

// there can only be no more than 32 modules
#define PERFORMANCE_STATS_ARRAY_SIZE 32
#define OS_OVERHEAD_SLOT             0

typedef struct PERFORMANCE_STATS {
    uint32_t start;
    uint32_t total_time;
    uint32_t total_runs;
    uint32_t average_run_time;
} performance_stats;



// variables
static uint32_t modules_size  = 0;

static performance_stats stats[PERFORMANCE_STATS_ARRAY_SIZE];

static uint32_t event_queue_misses = 0;


// functions 

void performance_init() {
    event_queue_misses = 0;

    memset(stats, 0, sizeof(performance_stats));

    modules_size = get_max_modules();

    // protections
    if (modules_size > PERFORMANCE_STATS_ARRAY_SIZE) {
        assert("Module Size must not exceed performance monitor array size.");
    }

}


void event_queue_miss() {
    event_queue_misses++;
}

// The operating system will alway be at slot zero

void os_overhead_start() {
    stats[OS_OVERHEAD_SLOT].start += get_current_time();  
}

void os_overhead_end() {
    uint32_t time = get_current_time();
    stats[OS_OVERHEAD_SLOT].total_time += time - stats[OS_OVERHEAD_SLOT].start;
    stats[OS_OVERHEAD_SLOT].total_runs++;
    stats[OS_OVERHEAD_SLOT].average_run_time = stats[OS_OVERHEAD_SLOT].total_time 
                                             / stats[OS_OVERHEAD_SLOT].total_runs;
}

void module_begin(uint32_t module_number) {
    if ( module_number < modules_size) {
        stats[module_number].start += get_current_time();  
    }
}

void module_end(uint32_t module_number) {
    if ( module_number < modules_size) {
        uint32_t time = get_current_time();
        stats[module_number].total_time += time - stats[module_number].start;
        stats[module_number].total_runs++;
        stats[module_number].average_run_time = stats[module_number].total_time / stats[module_number].total_runs;
    }
}

uint32_t test_get_performance_time(uint32_t slot) {
     return(stats[slot].total_time);
}

uint32_t test_get_performance_runs(uint32_t slot) {
     return(stats[slot].total_runs);
}

uint32_t test_get_performance_avg(uint32_t slot) {
     return(stats[slot].average_run_time);
}