

/*****************************************************

generic_module_one.h

Each module should have three defined functions:
XXXXX_init();
XXXXX_control(events E, unsigned int V);
XXXXX_cleanup();

XXXXX_init(); 
This is the  initilization code for that module. The 
code may or may not be needed but it should be defined.

XXXXX_control(events E, unsigned int V);
This is the main module code run by the scheduler. 
The event enumeration and the associated value is passed 
from the scheduler.

XXXXX_cleanup();
This is the code used for system shutdown. It's an 
opportunity to do shutdown tasks associated with the
module.

*****************************************************/

#ifndef GNERIC_MODULE_ONE_H
#define GNERIC_MODULE_ONE_H

#include "eventss.h" 

void generic_module_one_init();
void generic_module_one_control(events E, unsigned int V);
void generic_module_one_cleanup();

#endif // GNERIC_MODULE_ONE_H