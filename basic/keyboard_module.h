/*****************************************************

keyboard_module.h

*****************************************************/

#ifndef KEYBOARD_MODULE_H
#define KEYBOARD_MODULE_H

#include "controls.h" 

void keyboard_module_init();
void keyboard_module_control(controls C, unsigned int V);
void keyboard_module_cleanup();

#endif // KEYBOARD_MODULE_H