/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 

basic is an example program using EventShareOS in a POSIX 
Linux system. 
************************************************************/


/************************************************************

events.h


This is an event driven system.  Each event is called a 
a EVENT.  This is a custom enumeration as defined by the 
the needs of the system. There are two specific requirements
that cannot change for the events enumeration.  

Do not delete these enumerations:
EVENT_UNDEFINED is used marking a non-event or an empty event. 
EVENT_EOL is used for bounding of values and error checking

Each event name should start with EVENT
**************************************************************/


#ifndef EVENTS_H
#define EVENTS_H


typedef enum EVENTS
{
    EVENT_UNDEFINED  = 0,
    // ... put your EVENTs here  EVENTS_XXXXX

    // Keyboard events
    EVENT_KEYBOARD,
    EVENT_NEW_QUOTE,

    // Timer Events
    EVENT_TIMER_KEYBOARD_POLLING,    // 20 milliseconds,    0.02 seconds
    EVENT_TIMER_APP_DEMO,            // 30000  milliseconds, 30 seconds
    EVENT_TIMER_ONE_SHOT_DEMO,       // 5000   milliseconds, 5 seconds

    EVENT_EOL
} events;


#endif //EVENTS_H

