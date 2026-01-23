/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************
File: versioning.c
************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "versioning.h"


version_info app_version;

void set_app_version(uint32_t app_major, uint32_t app_minor, uint32_t app_build) {
    app_version.major = app_major;
    app_version.minor = app_minor;
    app_version.build = app_build;
}

void get_app_version(version_info * version_data) {
    version_data->major = app_version.major;
    version_data->minor = app_version.minor;
    version_data->build = app_version.build;
}


void get_app_version_string(char * version_string, uint32_t string_size) {
    char app_string[24];
    uint32_t size = sizeof(app_string);
    memset(app_string, 0, sizeof(app_string));

    if (size > string_size) {
        size = string_size;
    }

    snprintf(app_string, size, "%i.%i.%i", app_version.major, app_version.minor, app_version.build);
    memcpy(version_string, app_string, size);
}

int32_t compare_with_app_version(uint32_t major, uint32_t minor, uint32_t build) {
    int32_t answer = 0;
    uint32_t app = (app_version.major * 1000) + (app_version.minor * 100) + app_version.build;
    uint32_t compare = (major * 1000) + (minor*100) + build;

    if (app < compare ) {
        answer = -1;
    }
    else if (app == compare) {
        answer = 0;
    }
    else if (app > compare) {
        answer = 1;
    }
    return(answer);
}

int32_t compare_versions(const version_info * version1, const version_info * version2) {
    int32_t answer = 0;
    uint32_t app = (version1->major * 1000) + (version1->minor * 100) + version1->build;
    uint32_t compare = (version2->major * 1000) + (version2->minor * 100) + version2->build;

    if (app < compare ) {
        answer = -1;
    }
    else if (app == compare) {
        answer = 0;
    }
    else if (app > compare) {
        answer = 1;
    }
    return(answer);
}
