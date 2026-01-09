

/*****************************************************

generic_module_two.h

Each module should have three defined functions:
XXXXX_init();
XXXXX_control(events E, unsigned int V);
XXXXX_cleanup();

XXXXX_init(); 
This is the  initialization code for that module. The 
code may or may not be needed but it should be defined.

XXXXX_control(events C, unsigned int V);
This is the main module code run by the scheduler. 
The event enumeration and the associated value is passed 
from the scheduler.

XXXXX_cleanup();
This is the code used for system shutdown. It's an 
opportunity to do shutdown tasks associated with the
module.

*****************************************************/

#ifndef GNERIC_MODULE_TWO_H
#define GNERIC_MODULE_TWO_H

#include "events.h" 

void generic_module_two_init();
void generic_module_two_control(events C, unsigned int V);
void generic_module_two_cleanup();

#endif // GNERIC_MODULE_TWO_H