/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 

basic is an example program using EvenShareOS in a POSIX 
Linux system. 
************************************************************/


/*****************************************************

app_module.h

*****************************************************/

#ifndef APP_MODULE_H
#define APP_MODULE_H

#include "events.h" 

void app_module_init();
void app_module_control(events E, unsigned int V);
void app_module_cleanup();

#endif // APP_MODULE_H

