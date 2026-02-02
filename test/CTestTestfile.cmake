# CMake generated Testfile for 
# Source directory: /home/brian/code/c_code/EventShareOS/test
# Build directory: /home/brian/code/c_code/EventShareOS/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test_data_queue]=] "/home/brian/code/c_code/EventShareOS/test/TestDataQueue")
set_tests_properties([=[test_data_queue]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/brian/code/c_code/EventShareOS/test/CMakeLists.txt;23;add_test;/home/brian/code/c_code/EventShareOS/test/CMakeLists.txt;0;")
add_test([=[test_app_versioning]=] "/home/brian/code/c_code/EventShareOS/test/TestAppVersion")
set_tests_properties([=[test_app_versioning]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/brian/code/c_code/EventShareOS/test/CMakeLists.txt;31;add_test;/home/brian/code/c_code/EventShareOS/test/CMakeLists.txt;0;")
subdirs("binary_dir")
subdirs("Unity")
