/**
 * @file  cfgpath.impl.win32.h
 * @brief Cross platform methods for obtaining paths to configuration files.
 *
 * Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>
 * Copyright (C) 2019 LonghronShen <LonghronShen@hotmail.com>
 *
 * This code is placed in the public domain.  You are free to use it for any
 * purpose.  If you add new platform support, please contribute a patch!
 */

#if defined(_WIN32) || defined(WIN32) || defined(WIN64)

#ifndef CFGPATH_WIN32_H
#define CFGPATH_WIN32_H

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif

#if defined(CFGPATH_HEADER_ONLY)
#if defined(CFGPATH_IMPL)
#define CFGPATH_FUNC
#else
#define CFGPATH_FUNC static inline
#endif
#else
#define CFGPATH_FUNC
#endif

#if !defined(CFGPATH_HEADER_ONLY) && !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#if defined(NOMINMAX) || defined(CFGPATH_WIN_MINMAX)
#include <direct.h>
#include <shlobj.h>
#else
#define NOMINMAX
#include <direct.h>
#include <shlobj.h>
#undef NOMINMAX
#endif

// #define inline __inline
#define mkdir _mkdir
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif
#ifndef PATH_SEPARATOR_CHAR
#define PATH_SEPARATOR_CHAR '\\'
#endif
#ifndef PATH_SEPARATOR_STRING
#define PATH_SEPARATOR_STRING "\\"
#endif

CFGPATH_FUNC void get_user_config_file(char *out, size_t maxlen, const char *appname)
{
    if (maxlen < MAX_PATH)
    {
        out[0] = 0;
        return;
    }
    if (!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, out)))
    {
        out[0] = 0;
        return;
    }
    /* We don't try to create the AppData folder as it always exists already */
    size_t appname_len = strlen(appname);
    if (strlen(out) + 1 + appname_len + strlen(".ini") + 1 > maxlen)
    {
        out[0] = 0;
        return;
    }
    strcat(out, "\\");
    strcat(out, appname);
    strcat(out, ".ini");
}

CFGPATH_FUNC void get_user_config_folder(char *out, size_t maxlen, const char *appname)
{
    if (maxlen < MAX_PATH)
    {
        out[0] = 0;
        return;
    }
    if (!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, out)))
    {
        out[0] = 0;
        return;
    }
    /* We don't try to create the AppData folder as it always exists already */
    size_t appname_len = strlen(appname);
    if (strlen(out) + 1 + appname_len + 1 + 1 > maxlen)
    {
        out[0] = 0;
        return;
    }
    strcat(out, "\\");
    strcat(out, appname);
    /* Make the AppData\appname folder if it doesn't already exist */
    mkdir(out);
    strcat(out, "\\");
}

CFGPATH_FUNC void get_user_data_folder(char *out, size_t maxlen, const char *appname)
{
    /* No distinction under Windows or OS X */
    get_user_config_folder(out, maxlen, appname);
}

CFGPATH_FUNC void get_user_cache_folder(char *out, size_t maxlen, const char *appname)
{
    if (maxlen < MAX_PATH)
    {
        out[0] = 0;
        return;
    }
    if (!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, out)))
    {
        out[0] = 0;
        return;
    }
    /* We don't try to create the AppData folder as it always exists already */
    size_t appname_len = strlen(appname);
    if (strlen(out) + 1 + appname_len + 1 + 1 > maxlen)
    {
        out[0] = 0;
        return;
    }
    strcat(out, "\\");
    strcat(out, appname);
    /* Make the AppData\appname folder if it doesn't already exist */
    mkdir(out);
    strcat(out, "\\");
}
#endif

#endif