#ifndef EVENT_SHARE_OS_H
#define EVENT_SHARE_OS_H

/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

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


// Initialization Functions
// These need to be run before the super loop

/* 
Function: event_loop_set_events_range (uint32_t max)

EventShareOS needs to know the maximum number of 
events used by your program. This is to provide
a safety. It should look like this:
event_loop_set_events_range(EVENT_EOL); 
*/
void event_loop_set_events_range(uint32_t max);

/* 
Function: event_loop_set_modules_range(uint32_t max)

EventShareOS needs to know the maximum number of 
events used by your program. This is to provide
a safety. It should look like this:
event_loop_set_modules_range(MODULE_EOL); 
*/
void event_loop_set_modules_range(uint32_t max);

/* 
Function: event_loop_init

This initializes the event loop code.  
*/
void event_loop_init(void);

/*
Super Loop Functions:

The following functions are used in main 
for the super loop. In the following example,
the main loop is using an polling soft timers
vs. an interrupt driven system.  Depending on 
the systems needs, separate includes are 
provided for the soft timers.  

A polling main loop will look like this:

   while(event_loop_running()) {
       poll_time_keeper();
       event_loop_scheduler();
   }
*/


/* 
Function: event_loop_running
This function provides the mechanism to
break out of the super loop and shut down
the system.  
*/
bool event_loop_running();

/* 
Function: event_loop_scheduler
This is the heart of EventShareOS managing 
events and sending them to the module code. 
*/
void event_loop_scheduler(void);


// Module Functions

/* 
Function: subscribe(uint32_t module, int num, ...);

Events are shared between modules if they have been 
subscribed to the event. Please provide the module 
number, the number of events, and each event number.
*/
void subscribe(uint32_t module, int num, ...);

/*
Function: publish_event(uint32_t C, uint32_t V);

It is the act of publishing an event that drives
action in the system. Each event is sent as a 
pair Event and Value (E,V). The value can be 
any number as long as it's a unsigned 4 byte 
integer.  To send a float the function will be
called as such:
    float real_number = 5.4321;
    publish_event(EVENT_MY_FLOAT, (uint32_t) real_number);
*/
void publish_event(uint32_t E, uint32_t V);

/*
Function: signal_quit()
This sends a stop signal to EventShareOS to stop 
looping and start shutdown and cleanup. For embedded
systems, this will lead to a power off event. 
*/
void signal_quit();

// Timer Functions:

/* 
Function: add_timer_event(uint32_t E, uint16_t milliseconds, bool timer_type, bool on_off);

To add timers to the system provide an event number,
the time in miliseconds, the type: TIMER_REPEAT or 
TIMER_ONE_SHOT, and if the timer is turned on or off:
TIMER_ENABLED or TIMER_DISABLED.
*/
void add_timer_event(uint32_t E, uint16_t milliseconds, bool timer_type, bool on_off);

/*
Function: start_timer(uint32_t E);

To start a TIMER_ONE_SHOT provide the timer event number.
*/
void start_timer(uint32_t E);

/*
Function: enable_timer(uint32_t E, bool on_off);

Used to enable or disable repeating timers. Please
provide the timer event number and if it's on or off:
TIMER_ENABLED or TIMER_DISABLED.
*/
void enable_timer(uint32_t E, bool on_off);

/*
Function: cancel_timer(uint32_t E);

This is used to cancel one shot timers. For 
example this can be used for putting time outs
on network responses. 
*/
void cancel_timer(uint32_t E);


// UNDER CONSTRUCTION

/*
Function: event_data_set_chunks(uint32_t size, uint32_t count);

This sets the size and number of the data chunks.
The base memory is statically allocated. If the data 
chunk size and or count exceeds the static allocation, 
a runtime error will occur.  
*/
void event_data_set_chunks(uint32_t size, uint32_t count);

/*
Function: enqueue_data_chunk(uint32_t E, void * chunk, uint32_t size);

This places a data chunk into memory for use by other modules.
You must provide an Event Number, a pointer the the provided data,
and size.  If the size exceeds the data chunk size, a runtime 
error will occur. 

If the data is copied successfully, an event number will be 
published with a block number and true will be returned. A 
failed transfer will return false.

*/
bool enqueue_data_chunk(uint32_t E, uint8_t * chunk, uint32_t size);

/*
Function: get_data_chunk(uint32_t block_number, uint32_t module, void * data, uint32_t size);

This will copy the data needed into a modules local memory with the
provided memory pointer and size. block_numbers are a unique 
identifier for the data chunk. If the block_number does not match 
what is in memory, then function will return false indicating an error.  
*/
bool get_data_chunk(uint32_t chunk_id, uint8_t * data, uint32_t size);


#endif // EVENT_SHARE_OS_H