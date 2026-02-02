/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************
File: EventShare_config.h

These are the default configuration values needed to for 
EventShareOS. They can be overridden by including 
custom_event_config.h. This can override fixed values used
EventShareOS


CUSTOM_DATA_QUEUES_ENABLED
To use or not use data queues. Not all applications
need data block transfers.

CUSTOM_DATA_QUEUE_SIZE
The number of slots needed for transfer. This should be sized
according the maximum possibilities of data chunks at one time 
to prevent queue misses. 

CUSTOM_DATA_BLOCK_SIZE
The size of each block for data transfers. These should be sized
to the largest chunk needed for transfer.  The allocated memory
is block size X queue size.  For example a 32 byte block
size and 32 queue size is 1024 bytes. 

************************************************************/


#ifndef EVENTSHAREOS_CONFIG_H
#define EVENTSHAREOS_CONFIG_H

#ifdef CUSTOM_EVENT_CONFIG_H
    #include "custom_event_config.h" 
#endif


#ifdef CUSTOM_DATA_QUEUES_ENABLED
    #define EVENT_DATA_QUEUE_ENABLED  CUSTOM_DATA_QUEUES_ENABLED
#else
    #define EVENT_DATA_QUEUE_ENABLED  TRUE
#endif


// default data allocation is 4K 4096
#ifdef CUSTOM_DATA_QUEUE_SIZE
    #define EVENT_DATA_QUEUE_SIZE    CUSTOM_DATA_QUEUE_SIZE
#else
    #define EVENT_DATA_QUEUE_SIZE    16
#endif

#ifdef CUSTOM_DATA_BLOCK_SIZE
    #define EVENT_DATA_BLOCK_SIZE    CUSTOM_DATA_BLOCK_SIZE
#else    
    #define EVENT_DATA_BLOCK_SIZE    256
#endif

#endif // EVENTSHAREOS_CONFIG_H