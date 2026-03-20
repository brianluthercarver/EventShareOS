/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************
File: test_performance.c
************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "unity.h"
#include "EventShareOS.h"
#include "EventShareOS_test.h"
#include "performance.h"



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
    performance_init();

}

void tearDown(void) {
    // cleanup code
}



void test_recording_core_time() {
    uint32_t expected = 1000;
    uint32_t time = 0;
    uint32_t runs = 0;

    os_overhead_start();
    test_stimulate_timer(expected);
    os_overhead_end();
    
    runs = test_get_performance_runs(0);
    printf("test_recording_core_runs after %d   \n", runs);

    // OS is always slot zero
    time = test_get_performance_time(0); 
    TEST_ASSERT_EQUAL(expected, time);
}

void test_recording_core_runs() {
    uint32_t expected = 10;
    uint32_t runs = 0;

    runs = test_get_performance_runs(0);
    printf("test_recording_core_runs before %d   \n", runs);

    for(int i=0; i < 10; i++) {
        os_overhead_start();
        test_stimulate_timer(100);
        os_overhead_end();
    }
     // OS is always slot zero
    runs = test_get_performance_runs(0);
    printf("test_recording_core_runs after %d   \n", runs);
    TEST_ASSERT_EQUAL(expected, runs);
}

void test_recording_core_avg() {
    uint32_t expected = 10;
    uint32_t avg = 0;

    for(int i=0; i < 10; i++) {
        os_overhead_start();
        test_stimulate_timer(100);
        os_overhead_end();
    }
     // OS is always slot zero
    avg = test_get_performance_runs(0);
    TEST_ASSERT_EQUAL(expected, avg);
}


void test_recording_module_time(){
    uint32_t expected = 250;
    uint32_t time = 0;
    uint32_t runs = 0;

    runs = test_get_performance_runs(MODULE_TWO);
    printf("test_recording_module_time before %d  \n", runs);

    module_begin(MODULE_TWO);
    test_stimulate_timer(250);
    module_end(MODULE_TWO);

    time = test_get_performance_time(MODULE_TWO);

    runs = test_get_performance_runs(MODULE_TWO);
    printf("test_recording_module_time before %d  \n", runs);


    TEST_ASSERT_EQUAL(expected, time);
}

void test_recording_module_runs() {
    uint32_t expected = 100;
    uint32_t runs = 0;

    runs = test_get_performance_runs(MODULE_TWO);
    printf("test_recording_module_runs before %d  \n", runs);

    for (int i=0; i < 100; i++) {
        module_begin(MODULE_TWO);
        test_stimulate_timer(250);
        module_end(MODULE_TWO);
    }

    runs = test_get_performance_runs(MODULE_TWO);
    printf("test_recording_module_runs before %d  \n", runs);
    TEST_ASSERT_EQUAL(expected, runs);
}

void test_recording_module_avg() {
    uint32_t expected = 100;
    uint32_t avg = 0;
    uint32_t runs = 0;
    uint32_t time = 0;

    for (int i=0; i < 10; i++) {
        module_begin(MODULE_TWO);
        test_stimulate_timer(100);
        module_end(MODULE_TWO);
    }
    time = test_get_performance_time(MODULE_TWO);
    runs = test_get_performance_runs(MODULE_TWO);
    avg = test_get_performance_avg(MODULE_TWO);
    printf("test_recording_module_avg %d %d  %d  \n",time, runs, avg);
    TEST_ASSERT_EQUAL(expected, avg);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_recording_core_time);
    RUN_TEST(test_recording_core_runs);
    RUN_TEST(test_recording_core_avg);
    RUN_TEST(test_recording_module_time);
    RUN_TEST(test_recording_module_runs);
    RUN_TEST(test_recording_module_avg);

    return (UNITY_END());
}


