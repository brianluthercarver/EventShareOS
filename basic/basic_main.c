/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 

basic is an example program using EventShareOS in a POSIX 
Linux system. 
************************************************************/

/*****************************************************

basic_main.c

This is the main code to drive and test the basic 
integration of EventShareOS the eventloop code.

*****************************************************/

// standard libraries
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// eventloop code
#include "EventShareOS.h"
#include "posix_timer.h"

// customizations 
#include "events.h"
#include "modules.h"

int main(int argc, char *argv[]) {

    char os_version[64];

    memset(os_version, 0, sizeof(os_version));
    event_version_string(os_version, sizeof(os_version));
   
    // Execute the customization of the eventloop
    printf("main, Hello EventShareOS Basic Demo with keyboard and polling time!\n");
    printf("main, using EventShareOS verion %s \n", os_version);
    event_loop_set_events_range(EVENT_EOL);
    event_loop_set_modules_range(MODULE_EOL);
    timer_init();
    event_loop_init();
    init_poll_time_keeper();
    event_data_init_memory();

    while(event_loop_running()) {
        poll_time_keeper();
        event_loop_scheduler();
    }

}


