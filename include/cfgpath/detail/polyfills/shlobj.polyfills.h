/**
 * @file  shlobj.polyfills.h
 * @brief Cross platform methods for obtaining paths to configuration files.
 *
 * Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>
 * Copyright (C) 2019 LonghronShen <LonghronShen@hotmail.com>
 *
 * This code is placed in the public domain.  You are free to use it for any
 * purpose.  If you add new platform support, please contribute a patch!
 */

#if SHLOBJ_POLYFILLS_H
#define SHLOBJ_POLYFILLS_H

#ifdef CSIDL_APPDATA
#error This file should not be used under Windows, use the system version instead!
#endif

#define CSIDL_APPDATA 26 /* roaming appdata */
#define CSIDL_LOCAL_APPDATA 28

#define S_OK 0
#define S_FALSE 1
#define E_FAIL -1

#define SUCCEEDED(hr) ((hr) >= 0)

#define MAX_PATH 256

#endif