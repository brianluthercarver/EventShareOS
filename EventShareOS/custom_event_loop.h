/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/


/*****************************************************************
*
* custom_event_loop.h
*
* user custom implementation for the event loop.  These are called
* the internal functions
* 
*  
*******************************************************************/

#ifndef CUSTOM_EVENT_LOOP_H
#define CUSTOM_EVENT_LOOP_H

#include <stdint.h>

void custom_loop_init(void);
void custom_loop_scheduler(uint32_t module_list, uint32_t event, 
                           uint32_t value);
void custom_loop_quit(void);

#endif // CUSTOM_EVENT_LOOP_H
