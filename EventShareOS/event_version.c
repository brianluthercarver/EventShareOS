/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************

File: event_version

Description:
Needed functions for version control

************************************************************/

#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "event_version.h"

void event_version_string(char * return_buffer, uint32_t buffer_size ) {

    char version_string[32];
    char major[] = EVENTSHAREOS_MAJOR;
    char minor[] = EVENTSHAREOS_MINOR;
    char build[] = EVENTSHAREOS_BUILD;
    uint32_t size = sizeof(version_string);
    memset(version_string,0,sizeof(version_string));

    if (buffer_size < size) {
        size = buffer_size;
    }
    // build the string
    snprintf(version_string, sizeof(version_string), "%s.%s.%s", major, minor, build);
    memcpy(return_buffer, version_string, size);
}


