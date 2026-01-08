/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 

basic is an example program using EvenShareOS in a POSIX 
Linux system. 
************************************************************/

/*****************************************************

keyboard_module.h

*****************************************************/

#ifndef KEYBOARD_MODULE_H
#define KEYBOARD_MODULE_H

#include "events.h" 

void keyboard_module_init();
void keyboard_module_control(events C, unsigned int V);
void keyboard_module_cleanup();

#endif // KEYBOARD_MODULE_H