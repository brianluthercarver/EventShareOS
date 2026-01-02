

#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

/*****************************************************************
*
* eventloop.h
*
* Public interface file for the event loop
* 
* Event Loop is a round robin scheduler and event management framework.
* This is to promote hardware and module independence that allows proper
* testing of software modules.
*
* For main()
* There are two basic functions to impliment event_loop, setup and 
* execution. The init function should be called only once at the 
* begining. The scheduler is called within an infiniate loop. 
* 
*
* For Modules
* There are several functions to subscribe and publish events, as 
* well, as timer support. The quit signal can be used for shutdown 
* or act as a soft restart.
*
*******************************************************************/


#include <stdbool.h>
#include <stdint.h>


#include "../basic/controls.h"
#include "../basic/modules.h"

#define MAX_CONTROL_VALUES CONTROL_EOL
#define MAX_MODUULES 32

#define MODULE_01_MASK    0x00000001
#define MODULE_02_MASK    0x00000002
#define MODULE_03_MASK    0x00000004
#define MODULE_04_MASK    0x00000008
#define MODULE_05_MASK    0x00000010
#define MODULE_06_MASK    0x00000020
#define MODULE_07_MASK    0x00000040
#define MODULE_08_MASK    0x00000080
#define MODULE_09_MASK    0x00000100
#define MODULE_10_MASK    0x00000200
#define MODULE_11_MASK    0x00000400
#define MODULE_12_MASK    0x00000800
#define MODULE_13_MASK    0x00001000
#define MODULE_14_MASK    0x00002000
#define MODULE_15_MASK    0x00004000
#define MODULE_16_MASK    0x00008000
#define MODULE_17_MASK    0x00010000
#define MODULE_18_MASK    0x00020000
#define MODULE_19_MASK    0x00040000
#define MODULE_20_MASK    0x00080000
#define MODULE_21_MASK    0x00100000
#define MODULE_22_MASK    0x00200000
#define MODULE_23_MASK    0x00400000
#define MODULE_24_MASK    0x00800000
#define MODULE_25_MASK    0x01000000
#define MODULE_26_MASK    0x02000000
#define MODULE_27_MASK    0x04000000
#define MODULE_28_MASK    0x05000000
#define MODULE_29_MASK    0x10000000
#define MODULE_30_MASK    0x20000000
#define MODULE_31_MASK    0x40000000
#define MODULE_32_MASK    0x80000000


#define MAX_TIME_EVENTS  10
#define TIMER_ENABLED    true
#define TIMER_DISABLED   false
#define TIMER_REPEAT     true
#define TIMER_ONE_SHOT   false


typedef struct CONTROL_VALUE
{
    controls control;
    uint32_t value;
} control_value;


// these funcations are for main 
void event_loop_init(void);
void event_loop_scheduler(void);
bool event_loop_running();
void timer_init();
void time_keeper();

// these functions are for modules to use
void subscribe(modules module, int num, ...);
void publish_control(controls C, unsigned int V);
void signal_quit();
void add_timer_event(controls C, uint16_t milliseconds, bool timer_type, bool on_off);
void start_timer(controls C);
void enable_timer(controls C, bool on_off);
void cancel_timer(controls C);




#endif // EVENT_LOOP_H
