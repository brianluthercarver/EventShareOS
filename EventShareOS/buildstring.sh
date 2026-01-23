#!/bin/bash
#
# This creates the build string from the git describe command

rm -fv build_version.h

build_version_string=$(git describe --tags --always --match "v*")
echo $build_version_string

leading="#define EVENTSHAREOS_BUILD \"" 
trailing="\""


echo "// This file is automatically created by the build system." >> build_version.h
echo "// Do Not EDIT, instead edit version.h" >> build_version.h
echo " "                                      >> build_version.h


echo "#ifndef EVENTSHAREOS_BUILD_VERSION_H"   >> build_version.h
echo "#define EVENTSHAREOS_BUILD_VERSION_H"   >> build_version.h
echo " "                                      >> build_version.h
echo $leading$build_version_string$trailing   >> build_version.h 
echo " "                                      >> build_version.h
echo "#endif //EVENTSHAREOS_BUILD_VERSION_H"  >> build_version.h
