/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

#include <stdio.h>
#include <string.h>

#include "EventShareOS.h"

int main(int argc, char *argv[]) {

    char os_version[64];

    memset(os_version, 0, sizeof(os_version));
    event_version_string(os_version, sizeof(os_version));

    printf("main code for build purposes\n");
    printf("EventShareOS Version %s\n", os_version);

}