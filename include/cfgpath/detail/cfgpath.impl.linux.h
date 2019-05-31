/**
 * @file  cfgpath.impl.linux.h
 * @brief Cross platform methods for obtaining paths to configuration files.
 *
 * Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>
 * Copyright (C) 2019 LonghronShen <LonghronShen@hotmail.com>
 *
 * This code is placed in the public domain.  You are free to use it for any
 * purpose.  If you add new platform support, please contribute a patch!
 */

#if __linux__ || defined(__linux__)

#ifndef CFGPATH_LINUX_H
#define CFGPATH_LINUX_H

#if defined(CFGPATH_HEADER_ONLY)
#if defined(CFGPATH_IMPL)
#define CFGPATH_FUNC
#else
#define CFGPATH_FUNC static inline
#endif
#else
#define CFGPATH_FUNC
#endif

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef MAX_PATH
#undef MAX_PATH
#endif

#define MAX_PATH 512 /* arbitrary value */
#define PATH_SEPARATOR_CHAR '/'
#define PATH_SEPARATOR_STRING "/"

CFGPATH_FUNC void get_user_config_file(char *out, unsigned int maxlen, const char *appname)
{
    const char *out_orig = out;
    char *home = getenv("XDG_CONFIG_HOME");
    unsigned int config_len = 0;
    if (!home)
    {
        home = getenv("HOME");
        if (!home)
        {
            // Can't find home directory
            out[0] = 0;
            return;
        }
        config_len = strlen(".config/");
    }

    unsigned int home_len = strlen(home);
    unsigned int appname_len = strlen(appname);
    const int ext_len = strlen(".conf");

    /* first +1 is "/", second is terminating null */
    if (home_len + 1 + config_len + appname_len + ext_len + 1 > maxlen)
    {
        out[0] = 0;
        return;
    }

    memcpy(out, home, home_len);
    out += home_len;
    *out = '/';
    out++;
    if (config_len)
    {
        memcpy(out, ".config/", config_len);
        out += config_len;
        /* Make the .config folder if it doesn't already exist */
        mkdir(out_orig, 0755);
    }
    memcpy(out, appname, appname_len);
    out += appname_len;
    memcpy(out, ".conf", ext_len);
    out += ext_len;
    *out = 0;
}

CFGPATH_FUNC void get_user_config_folder(char *out, unsigned int maxlen, const char *appname)
{
    const char *out_orig = out;
    char *home = getenv("XDG_CONFIG_HOME");
    unsigned int config_len = 0;
    if (!home)
    {
        home = getenv("HOME");
        if (!home)
        {
            // Can't find home directory
            out[0] = 0;
            return;
        }
        config_len = strlen(".config/");
    }

    unsigned int home_len = strlen(home);
    unsigned int appname_len = strlen(appname);

    /* first +1 is "/", second is trailing "/", third is terminating null */
    if (home_len + 1 + config_len + appname_len + 1 + 1 > maxlen)
    {
        out[0] = 0;
        return;
    }

    memcpy(out, home, home_len);
    out += home_len;
    *out = '/';
    out++;
    if (config_len)
    {
        memcpy(out, ".config/", config_len);
        out += config_len;
        /* Make the .config folder if it doesn't already exist */
        *out = '\0';
        mkdir(out_orig, 0755);
    }
    memcpy(out, appname, appname_len);
    out += appname_len;
    /* Make the .config/appname folder if it doesn't already exist */
    *out = '\0';
    mkdir(out_orig, 0755);
    *out = '/';
    out++;
    *out = 0;
}

CFGPATH_FUNC void get_user_data_folder(char *out, unsigned int maxlen, const char *appname)
{
    const char *out_orig = out;
    char *home = getenv("XDG_DATA_HOME");
    unsigned int config_len = 0;
    if (!home)
    {
        home = getenv("HOME");
        if (!home)
        {
            // Can't find home directory
            out[0] = 0;
            return;
        }
        config_len = strlen(".local/share/");
    }

    unsigned int home_len = strlen(home);
    unsigned int appname_len = strlen(appname);

    /* first +1 is "/", second is trailing "/", third is terminating null */
    if (home_len + 1 + config_len + appname_len + 1 + 1 > maxlen)
    {
        out[0] = 0;
        return;
    }

    memcpy(out, home, home_len);
    out += home_len;
    *out = '/';
    out++;
    if (config_len)
    {
        memcpy(out, ".local/share/", config_len);
        out += config_len;
        /* Make the .local/share folder if it doesn't already exist */
        *out = '\0';
        mkdir(out_orig, 0755);
    }
    memcpy(out, appname, appname_len);
    out += appname_len;
    /* Make the .local/share/appname folder if it doesn't already exist */
    *out = '\0';
    mkdir(out_orig, 0755);
    *out = '/';
    out++;
    *out = 0;
}

CFGPATH_FUNC void get_user_cache_folder(char *out, unsigned int maxlen, const char *appname)
{
    const char *out_orig = out;
    char *home = getenv("XDG_CACHE_HOME");
    unsigned int config_len = 0;
    if (!home)
    {
        home = getenv("HOME");
        if (!home)
        {
            // Can't find home directory
            out[0] = 0;
            return;
        }
        config_len = strlen(".cache/");
    }

    unsigned int home_len = strlen(home);
    unsigned int appname_len = strlen(appname);

    /* first +1 is "/", second is trailing "/", third is terminating null */
    if (home_len + 1 + config_len + appname_len + 1 + 1 > maxlen)
    {
        out[0] = 0;
        return;
    }

    memcpy(out, home, home_len);
    out += home_len;
    *out = '/';
    out++;
    if (config_len)
    {
        memcpy(out, ".cache/", config_len);
        out += config_len;
        /* Make the .cache folder if it doesn't already exist */
        *out = '\0';
        mkdir(out_orig, 0755);
    }
    memcpy(out, appname, appname_len);
    out += appname_len;
    /* Make the .cache/appname folder if it doesn't already exist */
    *out = '\0';
    mkdir(out_orig, 0755);
    *out = '/';
    out++;
    *out = 0;
}

#endif

#endif