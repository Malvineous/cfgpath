cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

project(cfgpath LANGUAGES C CXX)

include(string_utils)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

if (MSVC)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif ()

# Get version from cfgpath.core.h
file(READ include/cfgpath/cfgpath.core.h core_h)
if (NOT core_h MATCHES "CFGPATH_VERSION ([0-9]+)([0-9][0-9])([0-9][0-9])")
  message(FATAL_ERROR "Cannot get CFGPATH_VERSION from core.h.")
endif ()

# Use math to skip leading zeros if any.
math(EXPR CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_MATCH_1})
math(EXPR CPACK_PACKAGE_VERSION_MINOR ${CMAKE_MATCH_2})
math(EXPR CPACK_PACKAGE_VERSION_PATCH ${CMAKE_MATCH_3})
join(CFGPATH_VERSION
    ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})

message(STATUS "Version: ${CFGPATH_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

include(CheckCXXCompilerFlag)

# Generate 'compile_commands.json' for clang_complete
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CXX_STD 14 CACHE STRING "Set to 11, 14, 17 or 20 to enable C++11, C++14, C++17 or C++20 builds, respectively." FORCE)
set(C_STD 11 CACHE STRING "Set to 99 or 11 to enable C99 or C11 builds, respectively." FORCE)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        add_compile_options("-Wno-c++11-extensions" "-Wno-c++11-long-long" "-Wno-deprecated-declarations")
    endif()
endif()

option(CFGPATH_BUILD_TESTS "Build with tests enabled." ON)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Define the cfgpath library, its includes and the needed defines.
file(GLOB CFGPATH_HEADER
    ${CMAKE_CURRENT_LIST_DIR}/include/cfgpath/*.h
    ${CMAKE_CURRENT_LIST_DIR}/include/cfgpath/detail/*.h
    ${CMAKE_CURRENT_LIST_DIR}/include/cfgpath/detail/polyfills/*.h)

file(GLOB CFGPATH_SRC
    ${CMAKE_CURRENT_LIST_DIR}/src/*.c
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(cfgpath ${CFGPATH_SRC} ${CFGPATH_HEADER} README.md)

if(APPLE)
  target_link_libraries(cfgpath "-framework Carbon")
endif()

add_library(cfgpath::cfgpath ALIAS cfgpath)

target_include_directories(cfgpath PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

set_target_properties(cfgpath PROPERTIES
  VERSION ${CFGPATH_VERSION} SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
  DEBUG_POSTFIX d)

if (BUILD_SHARED_LIBS)
  if (UNIX AND NOT APPLE)
    # Fix rpmlint warning:
    # unused-direct-shlib-dependency /usr/lib/libcfgpath.so.1.1.0 /lib/libm.so.6.
    target_link_libraries(cfgpath -Wl,--as-needed)
  endif ()
  target_compile_definitions(cfgpath PRIVATE CFGPATH_EXPORT INTERFACE CFGPATH_SHARED)
endif ()

add_library(cfgpath-header-only INTERFACE)
add_library(cfgpath::cfgpath-header-only ALIAS cfgpath-header-only)

target_compile_definitions(cfgpath-header-only INTERFACE CFGPATH_HEADER_ONLY=1)

target_include_directories(cfgpath-header-only INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

if(CFGPATH_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# installer
include(CPack)
