/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 

basic is an example program using EvenShareOS in a POSIX 
Linux system. 
************************************************************/


/*****************************************************

basic_eventloop.c

This is the implimentation of the custom functions used
by the event loop code.

All this code is called from the main event_loop engine.
The system is started and initilized, then executed by 
the scheduler, and finally stopped through the quit 
function. 

*****************************************************/
#include <stdio.h>

#include "EventShareOS.h"
#include "custom_event_loop.h"


// Put the various modules include code here
#include "modules.h"
#include "events.h"
#include "app_module.h"
#include "keyboard_module.h"
#include "quote_module.h"

void custom_loop_init(void) {

    // Set subscriptions for each module
    // The parameters are MODULE_NAME, subscription_count, events
    // For example:
    // subscribe(MODULE_NAME, 2, EVENT_ONE, EVENT_TWO)

    subscribe(MODULE_KEYBOARD, 1, EVENT_TIMER_KEYBOARD_POLLING );
    subscribe(MODULE_APP,      4, EVENT_KEYBOARD,
                                  EVENT_NEW_QUOTE,
                                  EVENT_TIMER_APP_DEMO,
                                  EVENT_TIMER_ONE_SHOT_DEMO );
    subscribe(MODULE_QUOTE,    1, EVENT_TIMER_APP_DEMO);                               


    // Set the soft timers
    // The parameters are EVENT_TIMER_XXXX, time, timer type, enabled/disabled
    // For example:
    // add_timer_event(EVENT_TIMER_XXXX, 300, TIMER_ONE_SHOT, TIMER_DISABLED)

    //EVENT_TIMER_KEYBOARD_POLLING,    // 0.02 seconds
    //EVENT_TIMER_APP_DEMO,            // 10 seconds
    //EVENT_TIMER_ONE_SHOT_DEMO,       // 5 seconds

    
    add_timer_event(EVENT_TIMER_APP_DEMO, 10000,  TIMER_REPEAT, TIMER_ENABLED);
    add_timer_event(EVENT_TIMER_KEYBOARD_POLLING, 100,  TIMER_REPEAT, TIMER_ENABLED);
    add_timer_event(EVENT_TIMER_ONE_SHOT_DEMO, 5000, TIMER_ONE_SHOT, TIMER_DISABLED);
    
    
    // Set the Data Chunk Size
    event_data_set_chunks(160, 10);

    
    app_module_init();
    keyboard_module_init();
    quote_module_init();


}


void custom_loop_scheduler(unsigned int module_list, events event, 
                           unsigned int value) {

    //printf("custom_loop_scheduler event %d, value %i \n", event, value);

    if (module_list & MODULE_01_MASK) {
        // call module 01 here
        keyboard_module_control(event, value);
    }

    if (module_list & MODULE_02_MASK) {
        // call module 01 here
        app_module_control(event, value);
    }

    if (module_list & MODULE_03_MASK) {
        // call module 03 here
        quote_module_control(event, value);
    }

    if (module_list & MODULE_04_MASK) {
        // call module 04 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_05_MASK) {
        // call module 05 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_06_MASK) {
        // call module 06 here
        // generic_module_call_control(event, value);
    }

        if (module_list & MODULE_07_MASK) {
        // call module 07 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_08_MASK) {
        // call module 08 here
        // generic_module_call_control(event, value);
    }

        if (module_list & MODULE_09_MASK) {
        // call module 09 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_10_MASK) {
        // call module 10 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_11_MASK) {
        // call module 11 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_12_MASK) {
        // call module 12 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_13_MASK) {
        // call module 13 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_14_MASK) {
        // call module 14 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_15_MASK) {
        // call module 15 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_16_MASK) {
        // call module 16 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_17_MASK) {
        // call module 17 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_18_MASK) {
        // call module 18 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_19_MASK) {
        // call module 19 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_20_MASK) {
        // call module 20 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_21_MASK) {
        // call module 21 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_22_MASK) {
        // call module 22 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_23_MASK) {
        // call module 23 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_24_MASK) {
        // call module 24 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_25_MASK) {
        // call module 25 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_26_MASK) {
        // call module 26 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_27_MASK) {
        // call module 27 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_28_MASK) {
        // call module 28 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_29_MASK) {
        // call module 29 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_30_MASK) {
        // call module 30 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_31_MASK) {
        // call module 31 here
        // generic_module_call_control(event, value);
    }

    if (module_list & MODULE_32_MASK) {
        // call module 32 here
        // generic_module_call_control(event, value);
    }

}
void custom_loop_quit(void) {
    app_module_cleanup();
    keyboard_module_cleanup();
    quote_module_cleanup();
}

