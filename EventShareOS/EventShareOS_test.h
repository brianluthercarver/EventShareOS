/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************

File: EventShareOS_test.h

Description:
EventShareOS_test.h is a series of functions that are avalible
to testing. They are not meant for production use.

************************************************************/

#ifndef EVENTSHAREOS_TEST_H
#define EVENTSHAREOS_TEST_H

#include <stdint.h>

/*
Function: test_event_data_blocks_used()

Returns the current number of blocks queued.
*/
uint32_t test_event_data_blocks_used();

/*
Function: test_event_data_blocks_free()

Returns the number of empty blocks
*/
uint32_t test_event_data_blocks_free();

/*
Function: uint32_t test_get_max_queue_size()

Returns the maximum slots for events
*/
uint32_t test_get_max_queue_size();

/*
Funciton: test_get_current_queue_count()

Returns the current number of items in the event queue
*/
uint32_t test_get_current_queue_count();

/*
Function: void test_clear_queue()

CLears the event queue of items. 
*/
void test_clear_queue();

/*
Function: test_module_count_per_event(event)

Returns the number of modules subscribed to an event
*/
uint32_t test_module_count_per_event(uint32_t event);


/*
Function: void test_stimulate_timer(uint32_t count)

Move the main timer forward like an interrupt. 
Used only for test purposes. 
*/
void test_stimulate_timer(uint32_t count);

/*
Function: test_dump_soft_timer_list() 

Dumps the entire list for humans
*/
void test_dump_soft_timer_list();

/*
Function: test_count_soft_timers()

Returns the number of timers in the list
*/
uint32_t test_count_soft_timers();

/*
Function: bool test_empty_timer_list()

Returns true if the timer list is empty
*/
bool test_empty_timer_list();

/*
Function: test_report_timer_status(uint32_t event)

Returns -1 Timer off, 0 Not Found, +1 Timer on
*/
int32_t test_report_timer_status(uint32_t event);


/*
Function: test_report_timer_type(uint32_t event)

Returns -1 Timer One Shot, 0 Not Found +1 Timer Repeat 
*/
int32_t test_report_timer_type(uint32_t event);



/*
FunctionL: test_get_performance_time(uint32_t slot)

Returns the total time for that module
*/
uint32_t test_get_performance_time(uint32_t slot);

/*
Function: test_get_performance_runs(uint32_t slot)

Returns the total number of runs for that module.
*/
uint32_t test_get_performance_runs(uint32_t slot); 

/*
Function: test_get_performance_avg(uint32_t slot)

Returns the average run time for that module
*/
uint32_t test_get_performance_avg(uint32_t slot);

/*
Function: void test_dump_performance_stats()

Displays the current status of the internal stats structure
*/
void test_dump_performance_stats();

#endif // EVENTSHAREOS_TEST_H