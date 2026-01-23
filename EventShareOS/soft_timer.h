/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************
Timer is a hardware driven software timers.  This is set 
for millisecond operation.  The hardware interupts updates
the main time keeper.  Then serches down the list of timer
events that need servicing.  

Timer events are set using the add_timer_event. There can
be only one timer per control.  If the add_timer_event is
called for an existing timer, the existing setup will be 
overwritten by the new parameters.
************************************************************/

#ifndef TIMER_H
#define TIMER_H



#include <stdbool.h>
#include <stdint.h>


typedef struct TIMER_EVENT {
    uint32_t control;
    uint16_t time;
    uint16_t count_down;
    uint8_t type;
    uint8_t enabled;
} timer_event;


void time_keeper();


#endif  //TIMER_H
