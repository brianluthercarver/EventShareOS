
/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************

File: event_data.c


************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "event_data.h"
#include "EventShareOS.h"
#include "EventShareOS_config.h"


#define EVENT_DATA_NO_NEED_TO_CLEAN  0xFFFFFFFF

typedef struct EVENT_DATA_RECORD {
    uint32_t id;
    uint32_t event;
    void * address;
    uint32_t size;
    bool clean;
}event_data_record;



// memory allocations based on custom configurations
// from EventShareOS_config.h

#if EVENT_DATA_QUEUE_ENABLED == TRUE
    bool data_enable = true;
    #define EVENT_DATA_MEMORY_SIZE (EVENT_DATA_QUEUE_SIZE * EVENT_DATA_BLOCK_SIZE)
#else
    bool data_enable = false;
    EVENT_DATA_QUEUE_SIZE 0
    EVENT_DATA_BLOCK_SIZE 0
#endif

static uint32_t block_number_id = 1;

static uint32_t next_empty_slot = 0;
static uint32_t total_slots_used = 0;
static uint32_t current_dequeued_slot = EVENT_DATA_NO_NEED_TO_CLEAN;

static uint8_t data_memory[EVENT_DATA_MEMORY_SIZE];
static event_data_record data_tracker[EVENT_DATA_QUEUE_SIZE];




// functions:


/* 
Function: clear_slot(uint32_t index)

Clears the slot in the data tracker. 
*/

void clear_slot(uint32_t index) {
    if (index < EVENT_DATA_QUEUE_SIZE) {
        data_tracker[index].id    = 0;
        data_tracker[index].event = 0;
        data_tracker[index].size  = 0;
        data_tracker[index].clean = true;
    }
}


/*
Function: set_memory_pointers()

This loads each slot with a fixed location in 
the data memory. 
*/

void set_memory_pointers() {

    uint8_t * memory_index = data_memory;
    for (uint32_t i = 0; i < EVENT_DATA_QUEUE_SIZE; i++) {
        clear_slot(i);
        data_tracker[i].address =  memory_index;
        memory_index += EVENT_DATA_BLOCK_SIZE * sizeof(uint8_t);
    }
}


/* 
Function: event_data_init_memory

Initializes the memory for use. The memory is set to zero 
and then blocks allocated in memory.    
*/
void event_data_init_memory() {
    if (data_enable) {

        next_empty_slot = 0;
        total_slots_used = 0;

        memset(&data_memory, 0, sizeof(data_memory));
        memset(data_tracker, 0, sizeof(data_tracker));

        set_memory_pointers();
    }

}


/*
Function: find_next_empty_slot()

This returns the location of the next empty slot.
If there are no more empty slots this will return
the current slot.
*/

void find_next_empty_slot() {
    uint32_t slot = next_empty_slot;
    bool done = false;
    uint32_t count = 0;
    while(!done) {
        slot++;
        if (slot >= EVENT_DATA_QUEUE_SIZE) {
            slot = 0; // go back to beginning
        }
        if (data_tracker[slot].clean == true) {
            next_empty_slot = slot;
            done = true;
        }
        if (count >= EVENT_DATA_QUEUE_SIZE) {
            done = true; // no more memory slots.
        }
        count++;
    }
}



uint32_t enqueue_data_chunk(uint32_t E, uint8_t * chunk, uint32_t size) {
    uint32_t id = 0;

    if (size < EVENT_DATA_BLOCK_SIZE) {
        // Check for an empty slot
        if (data_tracker[next_empty_slot].clean) {
            // empty slot found, the ID is a combination of a 
            // unique number and the slot number. This is to make
            // fast retrieval. 
            id = (block_number_id << 16) | next_empty_slot;
            data_tracker[next_empty_slot].id = id;
            data_tracker[next_empty_slot].clean = false;
            data_tracker[next_empty_slot].size = size;               
            memcpy(data_tracker[next_empty_slot].address, chunk, size);
            total_slots_used++;
            block_number_id++;
            publish_event(E, id);
            find_next_empty_slot();
        }
    }
    return(id);
}



bool get_data_chunk(uint32_t chunk_id, uint8_t * data, uint32_t size) {
    
    bool pass = false;
    uint32_t slot = chunk_id & 0x0000FFFF;
    
    // Range Check the slot number
    if (slot < EVENT_DATA_QUEUE_SIZE){
        // check for a match and size
        if (data_tracker[slot].id == chunk_id) {
            if (size >= data_tracker[slot].size) {      
                memcpy(data, data_tracker[slot].address, data_tracker[slot].size); 
                current_dequeued_slot = slot;
                pass = true;
            }
        }
    }
    return(pass);
}

void event_data_clean_slot() {
    if (current_dequeued_slot != EVENT_DATA_NO_NEED_TO_CLEAN ) {    
        total_slots_used--;   
        clear_slot(current_dequeued_slot);
        memset(data_tracker[current_dequeued_slot].address, 0, EVENT_DATA_BLOCK_SIZE);
        current_dequeued_slot = EVENT_DATA_NO_NEED_TO_CLEAN;
    }
}

uint32_t event_data_blocks_used() {
    return (total_slots_used);
}

uint32_t event_data_blocks_free() {
    return(EVENT_DATA_QUEUE_SIZE-total_slots_used);
}