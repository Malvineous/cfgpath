/**
 * @file  path_length.polyfills.h
 * @brief Cross platform methods for obtaining paths to configuration files.
 *
 * Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>
 * Copyright (C) 2019 LonghronShen <LonghronShen@hotmail.com>
 *
 * This code is placed in the public domain.  You are free to use it for any
 * purpose.  If you add new platform support, please contribute a patch!
 */

#ifndef PATH_LENGTH_POLYFILLS_H
#define PATH_LENGTH_POLYFILLS_H

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif
#endif

#if defined(_WIN32) || defined(WIN32) || defined(WIN64)

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifndef PATH_SEPARATOR_CHAR
#define PATH_SEPARATOR_CHAR '\\'
#endif

#ifndef PATH_SEPARATOR_STRING
#define PATH_SEPARATOR_STRING "\\"
#endif

#else

#ifndef PATH_SEPARATOR_CHAR
#define PATH_SEPARATOR_CHAR '/'
#endif

#ifndef PATH_SEPARATOR_STRING
#define PATH_SEPARATOR_STRING "/"
#endif

#if defined(__linux__)

#ifndef MAX_PATH
#define MAX_PATH 512 /* arbitrary value */
#endif

#elif defined(__APPLE__)

#ifndef MAX_PATH
#include <CoreServices/CoreServices.h>
#define MAX_PATH PATH_MAX
#endif

#endif
#endif

#endif