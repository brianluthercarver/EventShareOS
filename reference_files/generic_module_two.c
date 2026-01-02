#include "generic_module_two.h" 



void generic_module_two_init() {

    // I have nothing to initilize
}

void generic_module_two_control(controls C, unsigned int V) {

    // perform some action on C and V

    switch (C) {
        case CONTROL_GENERIC_ONE:
             break;
        case CONTORL_GENEROC_TWO:
             break;
        case CONTROL_TIMER_ONE:
            break;
        case CONTROL_TIMER_TWO:
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