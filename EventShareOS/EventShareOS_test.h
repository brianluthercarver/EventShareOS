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
Function: event_data_blocks_used()

Returns the current number of blocks queued.
*/
uint32_t event_data_blocks_used();

/*
Function: event_data_blocks_free()

Returns the number of empty blocks
*/
uint32_t event_data_blocks_free();


#endif // EVENTSHAREOS_TEST_H