
#include <stdio.h>

#include "app_module.h"
#include "event_loop.h"

static int timer_count = 0;

void app_module_init(){

    enable_timer(CONTROL_TIMER_ONE_SHOT_DEMO, TIMER_ENABLED);
}

void app_module_control(controls C, unsigned int V) {

    printf("control %d, value %i \n", C, V);
    switch(C) {
        case CONTROL_KEYBOARD:
            char c = (char) V;
            printf("App Control %c \n", c);

            if ((c == 'q') || (c == 'Q')) {
                printf("Program signal quit, shutting down\n");
                signal_quit();
            }
            break;

        case CONTROL_TIMER_APP_DEMO:
            timer_count++;
            if ((timer_count % 2) == 0) {
                start_timer(CONTROL_TIMER_ONE_SHOT_DEMO);
            }
            printf("10 Second repeat timer\n");
            break;

        case CONTROL_TIMER_ONE_SHOT_DEMO:
            printf("5 second one shot timer\n");
            break;

        default:
            break;
    }

}

void app_module_cleanup() {

}