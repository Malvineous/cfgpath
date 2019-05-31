cmake_minimum_required(VERSION 3.13)

project(cfgpath_tests VERSION 1.0.0 LANGUAGES C CXX)

file(GLOB CFGPATH_TESTS_SRC
    ${CMAKE_CURRENT_LIST_DIR}/*.c)

add_executable(cfgpath_test_runner ${CFGPATH_TESTS_SRC})
target_link_libraries(cfgpath_test_runner cfgpath)

add_test(cfgpath_test cfgpath_test_runner)
