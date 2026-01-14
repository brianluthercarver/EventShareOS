/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 

basic is an example program using EvenShareOS in a POSIX 
Linux system. 
************************************************************/

/*****************************************************

quote_module.h

*****************************************************/

#ifndef QUOTE_MODULE_H
#define QUOTE_MODULE_H

#include "events.h" 

void quote_module_init();
void quote_module_control(events C, unsigned int V);
void quote_module_cleanup();

#endif // QUOTE_MODULE_H