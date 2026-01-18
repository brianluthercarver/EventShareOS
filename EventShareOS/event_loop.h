/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/*****************************************************************
*
* eventloop.h
*
* Public interface file for the event loop
* 
* Event Loop is a round robin scheduler and event management framework.
* This is to promote hardware and module independence that allows proper
* testing of software modules.
*
* For main()
* There are two basic functions to impliment event_loop, setup and 
* execution. The init function should be called only once at the 
* begining. The scheduler is called within an infinite loop. 
* 
*
* For Modules
* There are several functions to subscribe and publish events, as 
* well, as timer support. The quit signal can be used for shutdown 
* or act as a soft restart.
*
*******************************************************************/

#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <stdbool.h>
#include <stdint.h>

typedef struct CONTROL_VALUE {
    uint32_t event;
    uint32_t value;
} control_value;

// internal functions for the timer module
uint32_t get_max_events();
uint32_t get_max_modules();


#endif // EVENT_LOOP_H
