
/*****************************************************

app_module.h

*****************************************************/

#ifndef APP_MODULE_H
#define APP_MODULE_H

#include "controls.h" 

void app_module_init();
void app_module_control(controls C, unsigned int V);
void app_module_cleanup();

#endif // APP_MODULE_H

