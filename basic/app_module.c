/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 

basic is an example program using EventShareOS in a POSIX 
Linux system. 
************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "events.h"
#include "app_module.h"
#include "EventShareOS.h"

static int timer_count = 0;
static char quote[160];
static uint32_t quote_count = 0;


void app_module_init(){

    memset(quote, 0, sizeof(quote));
    enable_timer(EVENT_TIMER_ONE_SHOT_DEMO, TIMER_ENABLED);
}

void app_module_control(events E, unsigned int V) {

    printf("APP MODULE event %d, value %i \n", E, V);
    switch(E) {
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
            printf("10 Second repeat timer %i\n", timer_count);
            break;

        case EVENT_NEW_QUOTE:
            memset(quote, 0, sizeof(quote));
            bool pass = get_data_chunk(V, (uint8_t *) quote, sizeof(quote));
            if (pass) {
                quote_count++;
                printf("New Quote %i:\n %s\n", quote_count, quote);     
            }
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