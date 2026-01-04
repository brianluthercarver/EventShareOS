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


#include <stdint.h>

// initialization functions 
void performance_set_controls_size(uint32_t max);
void performance_set_module_size(uint32_t max);
void performance_init();

// performance functions
void event_queue_miss();
void module_begin(uint32_t module_number);
