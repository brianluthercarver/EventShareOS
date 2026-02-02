/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************
File: test_data_queue.c
************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "unity.h"
#include "EventShareOS.h"
#include "event_data.h"


void setUp(void) {
    printf("test_data_queue setUp\n");
    // setup code
    // 32 slots at 32 bytes = 1024 bytes
    event_data_init_memory();
    event_loop_init();
}

void tearDown(void) {
    // cleanup code
}


/* 
Function: test_assert_usage()

Figuring out if assert true vs assert false

*/
void test_assert_usage() {

    TEST_ASSERT(true);       // pass
    //TEST_ASSERT(false);    // fail 
    //TEST_ASSERT(1 == 0);   // fail 
}

/*
Function: test_queue_size_limit

Set a queue size of 32 slots. Enqueue the entire
queue. Add one more and it should fail.

*/

void test_queue_size_limit() {

    char data[] = "1 1234567890 2 123456789 3 123456789 4 123456789 5 123456789 6 123456789 7 123456789 8 123456789 9 123456789 10 123456789";
    uint32_t queue_result = 0;


    // fill
    for (uint32_t i = 0; i < 16; i++) {
        queue_result = enqueue_data_chunk(1, (uint8_t *)data, sizeof(data));
        TEST_ASSERT( queue_result > 0);
    }

    // Test for one more, result should be false
    queue_result = enqueue_data_chunk(1, (uint8_t *)data, sizeof(data));
    TEST_ASSERT(queue_result == 0);
}

/*
Function: test_chunk_limit

Verifies that the enqueue functions rejects a too large data chunk.
The default size is 256 bytes, the data below is 10x30 = 300 bytes.

*/

void test_chunk_limit() {

    uint32_t queue_result = 0;
    uint8_t data[] = { 1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,
                       1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,
                       1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,
                       1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,
                       1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,
                       1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,
                       1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,
                       1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,
                       1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,
                       1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0};

    queue_result = enqueue_data_chunk(1, (uint8_t *)data, sizeof(data));
    TEST_ASSERT( queue_result == 0);
}


/*
Function: test_enqueue_dequeue()

Simple test to enqueue some data and retrieve the data
*/ 

void test_enqueue_dequeue() {
    char act[] = "1 1234567890 2 123456789 3 123456789 4 123456789 5 123456789 6 123456789 7 123456789 8 123456789 9 123456789 10 123456789";
    char exp[256];
    uint32_t queue_result = 0;
    bool pass = false;

    memset(exp, 0, sizeof(exp));
    
    queue_result = enqueue_data_chunk(1, (uint8_t *)act, sizeof(act));
    TEST_ASSERT(queue_result > 0);

    pass = get_data_chunk(queue_result, (uint8_t *)exp, sizeof(exp));
    TEST_ASSERT(pass);
    TEST_ASSERT_EQUAL_STRING(exp, act);
    
}

/*
Function: test_enqueue_dequeue_bad_id()

Testing for that the dequeue function returns false for a bad ID. 
*/
void test_enqueue_dequeue_bad_id() {
    char act[] = "1 1234567890 2 123456789 3 123456789 4 123456789 5 123456789 6 123456789 7 123456789 8 123456789 9 123456789 10 123456789";
    char exp[256];
    uint32_t queue_result = 0;
    bool pass = false;

    memset(exp, 0, sizeof(exp));
    
    queue_result = enqueue_data_chunk(1, (uint8_t *)act, sizeof(act));
    TEST_ASSERT(queue_result > 0);

    queue_result = 389457648;
    pass = get_data_chunk(queue_result, (uint8_t *)exp, sizeof(exp));
    TEST_ASSERT(pass == false);
    
}

/*
Function test_queue_size_count()

Verifies the number of items in the queue are correct.
Tests total used and total free
*/
void test_queue_size_count() {

    char data[] = "1 1234567890 2 123456789 3 123456789 4 123456789 5 123456789 6 123456789 7 123456789 8 123456789 9 123456789 10 123456789";
    uint32_t queue_result = 0;
    uint32_t total_blocks = 0;
    uint32_t free_blocks = 0;
    uint32_t used_blocks = 0;
    uint32_t expected = 12;
    
    // Get the current block allocation
    total_blocks = event_data_blocks_free();
    used_blocks = event_data_blocks_used();
    printf("total_blocks %i used_blocks %i expected %i\n", total_blocks, used_blocks, expected);

    TEST_ASSERT(used_blocks == 0);

    // fill
    for (uint32_t i = 0; i < expected; i++) {
        queue_result = enqueue_data_chunk(1, (uint8_t *)data, sizeof(data));
        TEST_ASSERT( queue_result > 0);
    }

    // check results;
    used_blocks = event_data_blocks_used();
    free_blocks = event_data_blocks_free();
    printf("total_blocks %i used_blocks %i free_blocks %i\n", total_blocks, used_blocks, free_blocks);

    TEST_ASSERT_EQUAL((total_blocks-expected), free_blocks);
    TEST_ASSERT_EQUAL(expected, used_blocks);
}


int main(void) {
    UNITY_BEGIN();
    printf("test_data_queue main\n");
    //RUN_TEST(test_assert_usage);
    RUN_TEST(test_queue_size_limit);
    RUN_TEST(test_chunk_limit);
    RUN_TEST(test_enqueue_dequeue);
    RUN_TEST(test_enqueue_dequeue_bad_id);
    RUN_TEST(test_queue_size_count);

    return (UNITY_END());
}
