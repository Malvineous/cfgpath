/**
 * @file  cfgpath.impl.osx.h
 * @brief Cross platform methods for obtaining paths to configuration files.
 *
 * Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>
 * Copyright (C) 2019 LonghronShen <LonghronShen@hotmail.com>
 *
 * This code is placed in the public domain.  You are free to use it for any
 * purpose.  If you add new platform support, please contribute a patch!
 */

#if __APPLE__ || defined(__APPLE__)

#ifndef CFGPATH_OSX_H
#define CFGPATH_OSX_H

#if defined(CFGPATH_HEADER_ONLY)
#if defined(CFGPATH_IMPL)
#define CFGPATH_FUNC
#else
#define CFGPATH_FUNC static inline
#endif
#else
#define CFGPATH_FUNC
#endif

#include <CoreServices/CoreServices.h>
#include <sys/stat.h>

#ifdef MAX_PATH
#undef MAX_PATH
#endif

#define MAX_PATH PATH_MAX
#define PATH_SEPARATOR_CHAR '/'
#define PATH_SEPARATOR_STRING "/"

CFGPATH_FUNC void get_user_config_file(char *out, unsigned int maxlen, const char *appname)
{
    FSRef ref;
    FSFindFolder(kUserDomain, kApplicationSupportFolderType, kCreateFolder, &ref);
    char home[MAX_PATH];
    FSRefMakePath(&ref, (UInt8 *)&home, MAX_PATH);
    /* first +1 is "/", second is terminating null */
    const char *ext = ".conf";
    if (strlen(home) + 1 + strlen(appname) + strlen(ext) + 1 > maxlen)
    {
        out[0] = 0;
        return;
    }

    strcpy(out, home);
    strcat(out, PATH_SEPARATOR_STRING);
    strcat(out, appname);
    strcat(out, ext);
}

CFGPATH_FUNC void get_user_config_folder(char *out, unsigned int maxlen, const char *appname)
{
    FSRef ref;
    FSFindFolder(kUserDomain, kApplicationSupportFolderType, kCreateFolder, &ref);
    char home[MAX_PATH];
    FSRefMakePath(&ref, (UInt8 *)&home, MAX_PATH);
    /* first +1 is "/", second is trailing "/", third is terminating null */
    if (strlen(home) + 1 + strlen(appname) + 1 + 1 > maxlen)
    {
        out[0] = 0;
        return;
    }

    strcpy(out, home);
    strcat(out, PATH_SEPARATOR_STRING);
    strcat(out, appname);
    /* Make the .config/appname folder if it doesn't already exist */
    mkdir(out, 0755);
    strcat(out, PATH_SEPARATOR_STRING);
}

CFGPATH_FUNC void get_user_data_folder(char *out, unsigned int maxlen, const char *appname)
{
    /* No distinction under Windows or OS X */
    get_user_config_folder(out, maxlen, appname);
}

CFGPATH_FUNC void get_user_cache_folder(char *out, unsigned int maxlen, const char *appname)
{
    /* No distinction under OS X */
    get_user_config_folder(out, maxlen, appname);
}

#endif

#endif