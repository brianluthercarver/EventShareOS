/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************

File: performance.h
Monitoring any systems performance is critical for system 
tuning or improvement. This file provides the functions needed
to monitoring all performance aspects of the system. This
includes: 

OS overhead
Module time
Event queue misses
Event queue depth

************************************************************/
#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <stdint.h>

// initialization functions 

/*
Function: performance_init()

Initializes the performance module. Clears the memory.
*/
void performance_init();

// performance functions

/*
Function: event_queue_miss()

Updates the number of times the queue rejected 
a publish_event.
*/
void event_queue_miss();

/*
Function: os_overhead_start()

Records the start time for the event_core functions
*/
void os_overhead_start();

/*
Function: os_overhead_end()

Records to the total time the event_core functions has ran. 
Calculates the average run time.
*/
void os_overhead_end();


#endif // PERFORMANCE_H