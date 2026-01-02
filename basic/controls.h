
#ifndef CONTROLS_H
#define CONTROLS_H


/************************************************************

controls.h


This is an event driven system.  Each event is called a 
a control.  This is a custom enumeration as defined by the 
the needs of the system. There are two specific requirements
that cannot change for the controls enumeration.  

Do not delete these enumerations:
CONTROL_UNDEFINED is used marking a non-event or an empty event. 
CONTROL_EOL is used for bounding of values and error checking

Each event name should start with CONTROL
**************************************************************/


typedef enum CONTROLS
{
    CONTROL_UNDEFINED  = 0,
    // ... put your controls here  CONTROLS_XXXXX

    // Keyboard events
    CONTROL_KEYBOARD,
  

    // Timer Events
    CONTROL_TIMER_KEYBOARD_POLLING,    // 20 milliseconds,    0.02 seconds
    CONTROL_TIMER_APP_DEMO,            // 30000  milliseconds, 30 seconds
    CONTROL_TIMER_ONE_SHOT_DEMO,       // 5000   milliseconds, 5 seconds

    CONTROL_EOL
} controls;


#endif //CONTROLS_H

