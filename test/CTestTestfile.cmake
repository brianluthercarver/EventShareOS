# CMake generated Testfile for 
# Source directory: /home/brian/code/c_code/EventShareOS/test
# Build directory: /home/brian/code/c_code/EventShareOS/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[app_versioning]=] "/home/brian/code/c_code/EventShareOS/test/TestAppVersion")
set_tests_properties([=[app_versioning]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/brian/code/c_code/EventShareOS/test/CMakeLists.txt;21;add_test;/home/brian/code/c_code/EventShareOS/test/CMakeLists.txt;0;")
subdirs("binary_dir")
subdirs("Unity")
