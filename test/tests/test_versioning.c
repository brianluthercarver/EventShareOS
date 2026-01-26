/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

#include <string.h>

#include "unity.h"
#include "versioning.h"

void setUp(void) {
    // setup code
}

void tearDown(void) {
    // cleanup code
}

void test_set_get_string() {

    char exp_string[] = "1.2.3";
    char act_string[12];
    
    memset(act_string, 0, sizeof(act_string));
    set_app_version(1,2,3);
    get_app_version_string(act_string, sizeof(act_string));
    TEST_ASSERT_EQUAL_STRING(exp_string, act_string);
}


void test_compare_number() {

    int32_t compare = 0;

    set_app_version(5,5,500);
    compare = compare_with_app_version(5,5,500);
    TEST_ASSERT_EQUAL(0,compare);

    compare = compare_with_app_version(5,5,400);
    TEST_ASSERT_UNLESS(compare < 0);

    compare = compare_with_app_version(5,5,600);
    TEST_ASSERT_UNLESS(compare > 0);

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_set_get_string);
    RUN_TEST(test_compare_number);
    return (UNITY_END());
}