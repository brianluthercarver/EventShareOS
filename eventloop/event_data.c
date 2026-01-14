
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
#include <assert.h>
#include <stdio.h>

#include "event_data.h"
#include "EventShareOS.h"

#define EVENT_DATA_MEMORY_SIZE       4096
#define EVENT_DATA_TRACKER_SIZE      16
#define EVENT_DATA_NO_NEED_TO_CLEAN  0xFFFFFFFF
typedef struct EVENT_DATA_RECORD {
    uint32_t id;
    uint32_t event;
    void * address;
    uint32_t size;
    bool clean;
}event_data_record;

static uint8_t data_memory[EVENT_DATA_MEMORY_SIZE];
static event_data_record data_tracker[EVENT_DATA_TRACKER_SIZE];

static uint32_t data_chunk_count = 0;
static uint32_t data_chunk_size = 0;
static uint32_t block_number_id = 1;

static uint32_t total_data_slots = 0;
static uint32_t total_slots_used = 0;
static uint32_t next_empty_slot = 0;
static uint32_t current_dequeued_slot = EVENT_DATA_NO_NEED_TO_CLEAN;


// functions:


/* 
Function: clear_slot(uint32_t index)

Clears the slot in the data tracker. 
*/

void clear_slot(uint32_t index) {
        //memset(data_tracker[index].address, 0, data_chunk_size);
        data_tracker[index].id    = 0;
        data_tracker[index].event = 0;
        data_tracker[index].size  = 0;
        data_tracker[index].clean = true;
}


/*
Function: set_memory_pointers()

This loads each slot with a fixed location in 
the data memory. 
*/

void set_memory_pointers() {

    uint8_t * memory_index = data_memory;
    //printf("set_memory_pointers %i \n", total_data_slots);
    for (uint32_t i = 0; i < total_data_slots; i++) {
        clear_slot(i);
        data_tracker[i].address =  memory_index;
        //printf("%i Data memory pointer %p ", i, (void *)memory_index);
        memory_index += data_chunk_size * sizeof(uint8_t);
        
    }
    printf("\n");
}

/*
Function: find_next_empty_slot()

This returns the location of the next empty slot.
If there are no more empty slots this will return
the current slot.
*/

uint32_t find_next_empty_slot() {
    uint32_t slot = next_empty_slot;
    bool done = false;
    bool count = 0;
    while(!done) {
        slot++;
        if (slot > EVENT_DATA_TRACKER_SIZE) {
            slot = 0; // go back to beginning
        }
        if (data_tracker[slot].clean == true) {
            next_empty_slot = slot;
            done = true;
        }
        if (count >= EVENT_DATA_TRACKER_SIZE) {
            done = true; // no more memory slots.
        }
        count++;
    }

}


/* 
Function: event_data_set_chunks

This sets the size of the data chunk size and 
how many.  If the size and count exceed the 
statically allocated memory, a run time error
will occur.  
*/
void event_data_set_chunks(uint32_t size, uint32_t count) {

    uint32_t total_size = size * count;
    if (total_size < sizeof(data_memory)) {
        total_slots_used = 0;
        total_data_slots = count;
        data_chunk_size  = size;
        data_chunk_count = count;
        next_empty_slot = 0;

        memset(&data_memory, 0, sizeof(data_memory));
        memset(data_tracker, 0, sizeof(data_tracker));

        set_memory_pointers();
    }
    else {
        assert("Allocated chunks exceed static memory allocation");
    }
}

bool enqueue_data_chunk(uint32_t E, uint8_t * chunk, uint32_t size) {
    bool pass = false;
    uint32_t block_number = block_number_id;
    uint32_t slot_number = 0;
 
    printf("enqueue_data_chunk %i %i", E, size);

    if (size < data_chunk_size) {
        // Check for an empty slot
        if (data_tracker[next_empty_slot].clean) {
                // empty slot found
                uint32_t id = (block_number_id << 16) | next_empty_slot;
                data_tracker[next_empty_slot].id = id;
                data_tracker[next_empty_slot].clean = false;
                data_tracker[next_empty_slot].size = size;               
                memcpy(data_tracker[next_empty_slot].address, chunk, size);
                //total_slots_used++;
                block_number_id++;
                publish_event(E, id);
                find_next_empty_slot();
                pass = true;
        }
    }
    else {
        assert("Data size exceeds chunk size");
    }

    return(pass);
}



bool get_data_chunk(uint32_t chunk_id, uint8_t * data, uint32_t size) {
    
    bool pass = false;
    uint32_t slot = chunk_id & 0x0000FFFF;

    // check for a match and size
    if (data_tracker[slot].id == chunk_id) {
        if (size >= data_tracker[slot].size) {      
            memcpy(data, data_tracker[slot].address, data_tracker[slot].size); 
            current_dequeued_slot = slot;
            pass = true;
        }
    }
    return(pass);
}

void event_data_clean_slot() {
    if (current_dequeued_slot != EVENT_DATA_NO_NEED_TO_CLEAN ) {       
        clear_slot(current_dequeued_slot);
        memset(data_tracker[current_dequeued_slot].address, 0, data_chunk_size);
        current_dequeued_slot = EVENT_DATA_NO_NEED_TO_CLEAN;
    }
}
