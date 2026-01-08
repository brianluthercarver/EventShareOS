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
void performance_set_controls_size(uint32_t max);
void performance_set_module_size(uint32_t max);
void performance_init();

// performance functions
void event_queue_miss();
void os_overhead_start();
void modules_start();

void module_begin(uint32_t module_number);


#endif // PERFORMANCE_H