/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************
File: test_versioning.c
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

    // versions are equal
    compare = compare_with_app_version(5,5,500);
    TEST_ASSERT_EQUAL(0,compare);
    
    // app is less than provided
    compare = compare_with_app_version(5,5,600);
    TEST_ASSERT_EQUAL(-1,compare);

    // app is greater than provided
    compare = compare_with_app_version(5,5,400);
    TEST_ASSERT_EQUAL(1,compare);
}

void test_compare_structs() {
    int result = 0;
    version_info reference = {5, 5, 500};
    version_info compare   = {5, 5, 500};

     // versions are equal
     result = compare_versions(&reference, &compare);
     TEST_ASSERT_EQUAL(0,result);

     // reference is less than compare
     compare.build = 600;
     result = compare_versions(&reference, &compare);
     TEST_ASSERT_EQUAL(-1,result);

     // reference is greater than compare
     compare.build = 400;
     result = compare_versions(&reference, &compare);
     TEST_ASSERT_EQUAL(1,result);
}

void test_get_app_version_struct() {
    version_info get_version;
    int compare = 0;
    set_app_version(5,5,500);
    get_app_version(&get_version);

    compare = compare_with_app_version(get_version.major, 
              get_version.minor, get_version.build);
    TEST_ASSERT_EQUAL(0,compare);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_set_get_string);
    RUN_TEST(test_compare_number);
    RUN_TEST(test_compare_structs);
    RUN_TEST(test_get_app_version_struct);
    return (UNITY_END());
}