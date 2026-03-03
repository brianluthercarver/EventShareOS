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

#endif // EVENTSHAREOS_TEST_H