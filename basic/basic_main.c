/*****************************************************

basic_main.c

This is the main code to drive and test the basic 
integration of EventShareOS the eventloop code.

*****************************************************/

// standard libraries
#include <stdio.h>
#include <stdbool.h>



// eventloop code
#include "../eventloop/eventloop.h"
#include "../eventloop/posix_timer.h"

int main(int argc, char *argv[]) {

    // Execute the customization of the eventloop
    printf("main, Hello EventShareOS Basic Demo with keyboard and polling time!\n");
    timer_init();
    event_loop_init();
    init_poll_time_keeper();

    while(event_loop_running()) {
        poll_time_keeper();
        event_loop_scheduler();
    }

}


