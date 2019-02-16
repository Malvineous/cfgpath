/**
 * @file  test-win-unicode.c
 * @brief cfgpath.h test code for the Windows, with Unicode support.
 *
 * Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>
 *
 * This code is placed in the public domain.  You are free to use it for any
 * purpose.  If you add new platform support, please contribute a patch!
 */

#include <string.h>
#include <stdio.h>

#define SHGetFolderPath test_SHGetFolderPath
#define mkdir test_mkdir
int test_mkdir(void *path);
int test_SHGetFolderPath(void *hwndOwner, int nFolder, void *hToken, int dwFlags, void *_pszPath);
#undef __linux__
#ifndef WIN32
#define WIN32
#endif
#ifndef UNICODE // enable unicode before #include-ing cfgpath.h
#define UNICODE
#endif
#include "cfgpath.h"

const cfgpathchar_t *set_appdata;
const cfgpathchar_t *set_appdata_local;
int set_retval;

/* Fake implementation of SHGetFolderPath() that fails when and how we want */
int test_SHGetFolderPath(void *hwndOwner, int nFolder, void *hToken,
	int dwFlags, void *_pszPath)
{
    // silence unused variable warnings
    (void)hwndOwner;
    (void)hToken;
    (void)dwFlags;

	/* Hopefully trigger an error if the buffer is too small */
    cfgpathchar_t *pszPath = (cfgpathchar_t*) _pszPath;
	pszPath[MAX_PATH - 1] = 0;

	switch (nFolder) {
		case CSIDL_APPDATA:
			if (set_appdata) {
				cfgpath__strcpy(pszPath, set_appdata);
				return set_retval;
			}
			break;
		case CSIDL_LOCAL_APPDATA:
			if (set_appdata_local) {
				cfgpath__strcpy(pszPath, set_appdata_local);
				return set_retval;
			}
			break;
	}
	return E_FAIL;
}

int test_mkdir(void *path)
{
	return 0;
    (void)path; // silence unused variable warning
}

int main(void)
{
	cfgpathchar_t buffer[MAX_PATH];

// get_user_config_file
    get_user_config_file(buffer, sizeof(buffer)/sizeof(buffer[0]), CFGPATHTEXT("myapp"));
    if (buffer[0] == 0) {
        printf("get_user_config_file() fail\n");
        return 1;
    }
    cfgpath__printf(CFGPATHTEXT("get_user_config_file() returned '%s'!\n"), buffer);

// get_user_config_folder
    get_user_config_folder(buffer, sizeof(buffer)/sizeof(buffer[0]), CFGPATHTEXT("myapp"));
    if (buffer[0] == 0) {
        printf("get_user_config_folder() fail\n");
        return 1;
    }
    cfgpath__printf(CFGPATHTEXT("get_user_config_folder() returned '%s'!\n"), buffer);

// get_user_data_folder
    get_user_data_folder(buffer, sizeof(buffer)/sizeof(buffer[0]), CFGPATHTEXT("myapp"));
    if (buffer[0] == 0) {
        printf("get_user_data_folder() fail\n");
        return 1;
    }
    cfgpath__printf(CFGPATHTEXT("get_user_data_folder() returned '%s'!\n"), buffer);

// get_user_cache_folder
    get_user_cache_folder(buffer, sizeof(buffer)/sizeof(buffer[0]), CFGPATHTEXT("myapp"));
    if (buffer[0] == 0) {
        printf("get_user_cache_folder() fail\n");
        return 1;
    }
    cfgpath__printf(CFGPATHTEXT("get_user_cache_folder() returned '%s'!\n"), buffer);

	printf("All tests passed for platform: Windows (Unicode).\n");
	return 0;
}
