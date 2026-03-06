/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************
File: test_soft_timer.c
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
    TIMER_EVENT_ONE,
    TIMER_EVENT_TWO,
    TIMER_EVENT_THREE,
    TIMER_EVENT_FOUR,
    TIMER_EVENT_FIVE,
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

    printf("test_soft_timer setUp\n");
    // setup code
    event_core_set_events_range(EVENT_EOL);
    event_core_set_modules_range(MODULE_EOL);

    event_data_init_memory();
    event_core_init();
    timer_init();
}

void tearDown(void) {
    // cleanup code
}


// check that list is not empty
void test_not_empty_list() {
    
    add_timer_event(TIMER_EVENT_ONE, 100, TIMER_REPEAT, TIMER_ENABLED);

    // check for an empty timer list
    bool empty = test_empty_timer_list();
    TEST_ASSERT_EQUAL(false, empty);

}


// add a repeating timer, check type and status
void test_add_timer_repeat_on() {
    
    // check for an empty timer list
    bool empty = test_empty_timer_list();
    int32_t status = 0;
    int32_t expected = 1;
    if (empty) {
        add_timer_event(TIMER_EVENT_ONE, 100, TIMER_REPEAT, TIMER_ENABLED);
        
        status = test_report_timer_type(TIMER_EVENT_ONE);
        TEST_ASSERT_EQUAL(expected, status);

        status = test_report_timer_status(TIMER_EVENT_ONE);
        TEST_ASSERT_EQUAL(expected, status);
    }
    else {
        TEST_ASSERT(empty);
    }
}

// add a repeating timer, check type and status
void test_add_timer_repeat_off() {
    
    // check for an empty timer list
    bool empty = test_empty_timer_list();
    int32_t status = 0;
    int32_t expected = 1;
    if (empty) {
        add_timer_event(TIMER_EVENT_ONE, 100, TIMER_REPEAT, TIMER_DISABLED);
        
        status = test_report_timer_type(TIMER_EVENT_ONE);
        TEST_ASSERT_EQUAL(expected, status);

        status = test_report_timer_status(TIMER_EVENT_ONE);
        expected = -1; // timer is disabled
        TEST_ASSERT_EQUAL(expected, status);
    }
    else {
        TEST_ASSERT(empty);
    }
}


// add a repeating timer enabled, then disable
void test_add_timer_repeat_on_disable() {
    
    // check for an empty timer list
    bool empty = test_empty_timer_list();
    int32_t status = 0;
    int32_t expected = -1;
    if (empty) {
        add_timer_event(TIMER_EVENT_ONE, 100, TIMER_REPEAT, TIMER_ENABLED);
        enable_timer(TIMER_EVENT_ONE, TIMER_DISABLED);
        status = test_report_timer_status(TIMER_EVENT_ONE);
        TEST_ASSERT_EQUAL(expected, status);
    }
    else {
        TEST_ASSERT(empty);
    }
}


// add a repeating timer disabled, then eanbled
void test_add_timer_repeat_on_enabled() {
    
    // check for an empty timer list
    bool empty = test_empty_timer_list();
    int32_t status = 0;
    int32_t expected = 1;
    if (empty) {
        add_timer_event(TIMER_EVENT_ONE, 100, TIMER_REPEAT, TIMER_DISABLED);
        enable_timer(TIMER_EVENT_ONE, TIMER_ENABLED);
        status = test_report_timer_status(TIMER_EVENT_ONE);
        TEST_ASSERT_EQUAL(expected, status);
    }
    else {
        TEST_ASSERT(empty);
    }
}

// add a one-shot timer, check type and status
void test_add_one_shot_enabled() {
    
    // check for an empty timer list
    bool empty = test_empty_timer_list();
    int32_t status = 0;
    int32_t expected = -1;
    if (empty) {

        add_timer_event(TIMER_EVENT_TWO, 100, TIMER_ONE_SHOT, TIMER_ENABLED);
        
        status = test_report_timer_type(TIMER_EVENT_TWO);
        TEST_ASSERT_EQUAL(expected, status);

        status = test_report_timer_status(TIMER_EVENT_TWO);
        expected = 1; // timer is enabled
        TEST_ASSERT_EQUAL(expected, status);
    }
    else {
        TEST_ASSERT(empty);
    }
}

// add a one-shot timer, check type and status
void test_add_one_shot_disabled() {
    
    // check for an empty timer list
    bool empty = test_empty_timer_list();
    int32_t status = 0;
    int32_t expected = -1;
    if (empty) {
        add_timer_event(TIMER_EVENT_TWO, 100, TIMER_ONE_SHOT, TIMER_DISABLED);
        
        status = test_report_timer_type(TIMER_EVENT_TWO);
        TEST_ASSERT_EQUAL(expected, status);

        status = test_report_timer_status(TIMER_EVENT_TWO);
        TEST_ASSERT_EQUAL(expected, status);
    }
    else {
        TEST_ASSERT(empty);
    }
}


// add a one-shot timer, disable and start
void test_add_one_shot_disabled_start() {
    
    // check for an empty timer list
    bool empty = test_empty_timer_list();
    int32_t status = 0;
    int32_t expected = 1;
    if (empty) {
        add_timer_event(TIMER_EVENT_TWO, 100, TIMER_ONE_SHOT, TIMER_DISABLED);
        start_timer(TIMER_EVENT_TWO);

        status = test_report_timer_status(TIMER_EVENT_TWO);
        TEST_ASSERT_EQUAL(expected, status);
    }
    else {
        TEST_ASSERT(empty);
    }
}

// add a one-shot timer, canceled
void test_add_one_shot_enable_cancel() {
    
    // check for an empty timer list
    bool empty = test_empty_timer_list();
    int32_t status = 0;
    int32_t expected = -1;
    if (empty) {
        add_timer_event(TIMER_EVENT_TWO, 100, TIMER_ONE_SHOT, TIMER_DISABLED);
        cancel_timer(TIMER_EVENT_TWO);

        status = test_report_timer_status(TIMER_EVENT_TWO);
        TEST_ASSERT_EQUAL(expected, status);
    }
    else {
        TEST_ASSERT(empty);
    }
}

// add repeating timer enable can't cancel
// cancel_timer is not allowed on repeating
void test_repeating_timer_cancel() {
    // check for an empty timer list
    bool empty = test_empty_timer_list();
    int32_t status = 0;
    int32_t expected = 1;
    if (empty) {
        add_timer_event(TIMER_EVENT_THREE, 100, TIMER_REPEAT, TIMER_ENABLED);
        cancel_timer(TIMER_EVENT_THREE);
        status = test_report_timer_status(TIMER_EVENT_THREE);
        TEST_ASSERT_EQUAL(expected, status);
    }
    else {
        TEST_ASSERT(empty);
    }    
}

// add one-shot timer enable can't enable
void test_one_shot_timer_enable() {
    // check for an empty timer list
    bool empty = test_empty_timer_list();
    int32_t status = 0;
    int32_t expected = -1;
    if (empty) {
        add_timer_event(TIMER_EVENT_FOUR, 100, TIMER_ONE_SHOT, TIMER_DISABLED);
        uint32_t count = test_count_soft_timers();
        printf("Timer_four count add %d\n", count);
        status = test_report_timer_type(TIMER_EVENT_FOUR);
        TEST_ASSERT_EQUAL(expected, status);
        enable_timer(TIMER_EVENT_FOUR, TIMER_ENABLED);
        status = test_report_timer_status(TIMER_EVENT_FOUR);
        TEST_ASSERT_EQUAL(expected, status);
    }
    else {
        TEST_ASSERT(empty);
    }    
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_not_empty_list);
    RUN_TEST(test_add_timer_repeat_on); 
    RUN_TEST(test_add_timer_repeat_off); 
    RUN_TEST(test_add_timer_repeat_on_disable);
    RUN_TEST(test_add_timer_repeat_on_enabled);
    RUN_TEST(test_add_one_shot_enabled); 
    RUN_TEST(test_add_one_shot_disabled);
    RUN_TEST(test_add_one_shot_disabled_start);  
    RUN_TEST(test_add_one_shot_enable_cancel); 
    RUN_TEST(test_repeating_timer_cancel);
    RUN_TEST(test_one_shot_timer_enable);
    return (UNITY_END());
}