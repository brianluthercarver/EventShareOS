/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 

basic is an example program using EvenShareOS in a POSIX 
Linux system. 
************************************************************/

#include <stdio.h>

#include "events.h"
#include "app_module.h"
#include "EventShareOS.h"

static int timer_count = 0;

void app_module_init(){

    enable_timer(EVENT_TIMER_ONE_SHOT_DEMO, TIMER_ENABLED);
}

void app_module_control(events C, unsigned int V) {

    printf("event %d, value %i \n", C, V);
    switch(C) {
        case EVENT_KEYBOARD:
            char c = (char) V;
            printf("App Control %c \n", c);

            if ((c == 'q') || (c == 'Q')) {
                printf("Program signal quit, shutting down\n");
                signal_quit();
            }
            break;

        case EVENT_TIMER_APP_DEMO:
            timer_count++;
            if ((timer_count % 2) == 0) {
                start_timer(EVENT_TIMER_ONE_SHOT_DEMO);
            }
            printf("10 Second repeat timer\n");
            break;

        case EVENT_TIMER_ONE_SHOT_DEMO:
            printf("5 second one shot timer\n");
            break;

        default:
            break;
    }

}

void app_module_cleanup() {

}