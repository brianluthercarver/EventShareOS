
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

#include "event_data.h"

#define EVENT_DATA_MEMORY_SIZE  256
#define EVENT_DATA_TRACKER_SIZE 16

typedef struct EVENT_DATA_RECORD {
    uint32_t block_number;
    uint32_t modules;
    void * block_address;
    bool dirty;
}event_data_record;

uint8_t data_memory[EVENT_DATA_MEMORY_SIZE];
event_data_record data_tracker[EVENT_DATA_TRACKER_SIZE];

uint32_t data_chunk_count = 0;
uint32_t data_chunk_size = 0;

// functions:

// function: event_data_set_chunks
// This sets the size of the data chunk size and 
// how many.  If the size and count exceed the 
// statically allocated memory, a run time error
// will occur. 
void event_data_set_chunks(uint32_t size, uint32_t count) {

    uint32_t total_size = size * count;
    if (total_size < sizeof(data_memory)) {
        data_chunk_size  = size;
        data_chunk_count = count;

        memset(&data_memory, 0, sizeof(data_memory));
        memset(data_tracker, 0, sizeof(data_tracker));
    }
    else {
        assert("Allocated chunks exceed static memory allocation");
    }
}