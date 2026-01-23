/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 
************************************************************/

/************************************************************
File: versioning.h

Versioning Management functions for the applications. The 
version number and build information must be stored as
integer values.  This is to provide a comparision function
for upgrades or downgrades of application code.
************************************************************/

#ifndef VERSIONING_H
#define VERSIONING_H

#include <stdio.h>
#include <stdint.h>

typedef struct VERSION_INFO {
    uint32_t major;
    uint32_t minor;
    uint32_t build;
} version_info;


/* 
Function: set_app_version(uint32_t app_major, uint32_t app_minor, uint32_t app_build)

Stores the current version information of the application running
EventShareOS. This different from EventShareOS version.
*/
void set_app_version(uint32_t app_major, uint32_t app_minor, uint32_t app_build); 

/* 
Function: get_app_version(version_info * version_data)

Sets the current into the version_info structure
*/
void get_app_version(version_info * version_data);

/* 
Function: get_app_version_string(char * version_string, uint32_t string_size)

Copies the app version information into a dot string
*/
void get_app_version_string(char * version_string, uint32_t string_size);

/*
Function: compare_with_app_version(uint32_t major, uint32_t minor, uint32_t build)

Passing in a version information as discrete numbers 
and compares with the current application version.  
The return is a signed number from -1 to 1
-1  Application version is less than provided.
 0  Application version is the same as provided.
 1  Application version is greater than provided.
*/
int32_t compare_with_app_version(uint32_t major, uint32_t minor, uint32_t build);

/*
Function: compare_versions(const version_data * version1, const version_data * version2)

Compares two version_info structures against each other. 
The return is a signed number from -1 to 1
-1  version1 is less than version2.
 0  version1 is the same as version2.
 1  version1 is greater than version2.
*/
int32_t compare_versions(const version_info * version1, const version_info * version2);

#endif // VERSIONING_H

