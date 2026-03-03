/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/


/*****************************************************************
*
* custom_event_core.h
*
* user custom implementation for the event core functions.
* 
*  
*******************************************************************/

#ifndef CUSTOM_EVENT_CORE_H
#define CUSTOM_EVENT_CORE_H

#include <stdint.h>

void custom_core_init(void);
void custom_core_scheduler(uint32_t module_list, uint32_t event, 
                           uint32_t value);
void custom_core_quit(void);

#endif // CUSTOM_EVENT_CORE_H
