
#ifndef MODULES_H
#define MODULES_H


/************************************************************
modules.h

This is an event driven system.  
Modules are like processes or threads. Each module consume 
events and are passive. Unless there is an event for a 
module, it does not get get executed. 

 Place your module names here.  Do not delete MODULE_EOL 

 There can be 32 different modules, see eventloop.h

**************************************************************/

typedef enum MODULES
{
    MODULE_NONE,

    // ... put your module names here  MODULE_XXXXX
    MODULE_KEYBOARD,
    MODULE_APP,  

    // do not delete
    MODULE_EOL   
} modules;


#endif //MODULES_H

