#ifndef EVENT_SHARE_OS_H
#define EVENT_SHARE_OS_H



/************************************************************

File: EventShareOS

Description:
EventShareOS is set of library files to provide an Event Driven
Cooperative Operating System.

This is the needed header file to access the functions provided
by EventShareOS. 

************************************************************/

// standard libary includes
#include <stdbool.h>
#include <stdint.h>


// Definitions
// These definitions are used for the modules and functions.
// Do not change them. 


#define MAX_MODULES 32

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
#define MODULE_28_MASK    0x08000000
#define MODULE_29_MASK    0x10000000
#define MODULE_30_MASK    0x20000000
#define MODULE_31_MASK    0x40000000
#define MODULE_32_MASK    0x80000000


#define MAX_TIME_EVENTS  10
#define TIMER_ENABLED    true
#define TIMER_DISABLED   false
#define TIMER_REPEAT     true
#define TIMER_ONE_SHOT   false


// Function Definitions



// these funcations are for main 
void event_loop_set_controls_range(uint32_t max);
void event_loop_set_modules_range(uint32_t max);
void event_loop_init(void);
void event_loop_scheduler(void);
bool event_loop_running();
void timer_init();
void time_keeper();

// these functions are for modules to use
void subscribe(uint32_t module, int num, ...);
void publish_control(uint32_t C, uint32_t V);
void signal_quit();
void add_timer_event(uint32_t C, uint16_t milliseconds, bool timer_type, bool on_off);
void start_timer(uint32_t C);
void enable_timer(uint32_t C, bool on_off);
void cancel_timer(uint32_t C);

void event_data_set_chunks(uint32_t size, uint32_t count);
uint32_t enqueue_data_chunk(uint32_t C, void * chunk, uint32_t size);
void get_data_chunk(uint32_t block_number, uint32_t module, void * data, uint32_t size);


#endif // EVENT_SHARE_OS_H