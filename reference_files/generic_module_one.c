#include "generic_module_one.h" 



void generic_module_one_init() {

    // I have nothing to initilize
}

void generic_module_one_control(events C, unsigned int V) {

    // perform some action on E and V

    switch (C) {
        case EVENT_GENERIC_ONE:
             break;
        case CONTORL_GENEROC_TWO:
             break;
        case EVENT_TIMER_ONE:
            break;
        case EVENT_TIMER_TWO:
            break;
        defualt:
            // if the subscriptions are done correctly, this should never happen
            // better safe than sorry
            break;
    }
}


void generic_module_one_cleanup() {
    // I have nothing to cleanup
}