/*****************************************************

basic_main.c

This is the main code to drive and test the basic 
integration of EventShareOS the eventloop code.

*****************************************************/

// standard libraries
#include <stdio.h>
#include <stdbool.h>

// eventloop code
#include "event_loop.h"
#include "posix_timer.h"

// customizations 
#include "controls.h"
#include "modules.h"

int main(int argc, char *argv[]) {

    // Execute the customization of the eventloop
    printf("main, Hello EventShareOS Basic Demo with keyboard and polling time!\n");
    event_loop_set_controls_range(CONTROL_EOL);
    event_loop_set_modules_range(MODULE_EOL);
    timer_init();
    event_loop_init();
    init_poll_time_keeper();

    while(event_loop_running()) {
        poll_time_keeper();
        event_loop_scheduler();
    }

}


