/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************
File: test_eventloop.c
************************************************************/

#include <stdint.h>

#include "custom_event_core.h"


void custom_core_init(void) {

}

void custom_core_scheduler(uint32_t module_list, uint32_t event, 
                           uint32_t value) {
    module_list = module_list;
    event = event;
    value = value;                        

}


void custom_core_quit(void) {

}