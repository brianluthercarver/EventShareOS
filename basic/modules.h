/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 

basic is an example program using EvenShareOS in a POSIX 
Linux system. 
************************************************************/

/************************************************************
modules.h

This is an event driven system.  
Modules are like processes or threads. Each module consume 
events and are passive. Unless there is an event for a 
module, it does not get get executed. 

 Place your module names here.  Do not delete MODULE_EOL 

 There can be 32 different modules, see eventloop.h

**************************************************************/

#ifndef MODULES_H
#define MODULES_H


typedef enum MODULES
{
    MODULE_NONE,

    // ... put your module names here  MODULE_XXXXX
    MODULE_KEYBOARD,
    MODULE_APP,  
    MODULE_QUOTE,

    // do not delete
    MODULE_EOL   
} modules;


#endif //MODULES_H

