#include "generic_module_two.h" 



void generic_module_two_init() {

    // I have nothing to initilize
}

void generic_module_two_control(events E, unsigned int V) {

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

void generic_module_two_cleanup() {
    // I have nothing to cleanup
}