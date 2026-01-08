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