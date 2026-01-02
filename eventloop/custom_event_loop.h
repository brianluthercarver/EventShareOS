

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





void custom_loop_init(void);
void custom_loop_scheduler(unsigned int module_list, controls control, 
                           unsigned int value);
void custom_loop_quit(void);

#endif // CUSTOM_EVENT_LOOP_H
