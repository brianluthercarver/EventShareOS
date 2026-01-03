

#ifndef CUSTOM_EVENT_LOOP_H
#define CUSTOM_EVENT_LOOP_H

/*****************************************************************
*
* custom_event_loop.h
*
* user custom implementation for the event loop.  These are called
* the internal functions
* 
*  
*******************************************************************/


#include <stdint.h>



void custom_loop_init(void);
void custom_loop_scheduler(uint32_t module_list, uint32_t control, 
                           uint32_t value);
void custom_loop_quit(void);

#endif // CUSTOM_EVENT_LOOP_H
