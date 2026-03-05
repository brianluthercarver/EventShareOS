/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************
File: test_event_core.c
************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "unity.h"
#include "EventShareOS.h"
#include "EventShareOS_test.h"


typedef enum EVENTS
{
    EVENT_UNDEFINED  = 0,
    // ... put your EVENTs here  EVENTS_XXXXX
    EVENT_ONE,
    EVENT_TWO,
    EVENT_THREE,
    EVENT_FOUR,
    EVENT_FIVE,
    EVENT_EOL
} events;

typedef enum MODULES
{
    MODULE_NONE,

    // ... put your module names here  MODULE_XXXXX
    MODULE_ONE,
    MODULE_TWO,
    MODULE_THREE,

    // do not delete
    MODULE_EOL   
} modules;

void setUp(void) {

    printf("test_event_core setUp\n");
    // setup code
    event_core_set_events_range(EVENT_EOL);
    event_core_set_modules_range(MODULE_EOL);

    event_data_init_memory();
    event_core_init();
}

void tearDown(void) {
    // cleanup code
}

// ensure that events are added to the queue 
void test_event_queue_count() {
    const uint32_t expected = 5;
    uint32_t count = 0;
    publish_event(EVENT_ONE, 0);
    publish_event(EVENT_TWO, 0);
    publish_event(EVENT_THREE, 0);
    publish_event(EVENT_FOUR, 0);
    publish_event(EVENT_FIVE, 0);
    count = test_get_current_queue_count();
    TEST_ASSERT_EQUAL(expected, count);

}

// this test will overload the queue
// each add on a full queue will be dropped
void test_event_queue_overload() {
    uint32_t expected = test_get_max_queue_size();
    uint32_t count = 0;
    for(uint32_t i =0; i < (expected+5); i++) {
        publish_event(EVENT_ONE, 1);
    }
    count = test_get_current_queue_count(); 
    TEST_ASSERT_EQUAL(expected, count);
}

// verify that the number of modules match
// for an event
void test_subscriptions() {

    uint32_t expected = 0;
    uint32_t count = 0;
    subscribe(MODULE_ONE, 1, EVENT_ONE);
    subscribe(MODULE_TWO, 3, EVENT_ONE, EVENT_TWO, EVENT_THREE);
    subscribe(MODULE_THREE, 5, EVENT_ONE, EVENT_TWO, EVENT_THREE, EVENT_FOUR, EVENT_FIVE);

    // check event one
    expected = 3;
    count = test_module_count_per_event(EVENT_ONE);
    TEST_ASSERT_EQUAL(expected, count);
    
    // check event three
    expected = 2;
    count = test_module_count_per_event(EVENT_THREE);
    TEST_ASSERT_EQUAL(expected, count);

    // check event five
    expected = 1;
    count = test_module_count_per_event(EVENT_FIVE);
    TEST_ASSERT_EQUAL(expected, count);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_event_queue_count);
    RUN_TEST(test_event_queue_overload);
    RUN_TEST(test_subscriptions);
    return (UNITY_END());
}


