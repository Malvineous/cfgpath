/**
 * @file  test-osx.c
 * @brief cfgpath.h test code for the OS X platform.
 *
 * Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>
 * Copyright (C) 2019 LonghronShen <LonghronShen@hotmail.com>
 *
 * This code is placed in the public domain.  You are free to use it for any
 * purpose.  If you add new platform support, please contribute a patch!
 */

#if __APPLE__

#undef WIN32
#undef _WIN32
#undef __linux__

#include <string.h>
#include <stdio.h>

#define CFGPATH_HEADER_ONLY

#ifdef FSRefMakePath
#undef FSRefMakePath
#define FSRefMakePath test_FSRefMakePath
#endif

#ifdef mkdir
#undef mkdir
#define mkdir test_mkdir
#endif

#include <cfgpath/cfgpath.h>

#define HOME_VALUE "/Users/test/Library/Application Support/"
#define XDG_CONFIG_HOME_VALUE HOME_VALUE ".config"

int test_env_xdg_valid;  /* Does $XDG_CONFIG_HOME exist? */
int test_env_home_valid; /* Does $HOME exist? */

OSStatus test_FSRefMakePath(const FSRef *ref, UInt8 *path, UInt32 pathBufferSize)
{
    printf("calling mock function test_FSRefMakePath.\r\n");
    memset((void *)path, 0, pathBufferSize);
    strcpy((char *)path, HOME_VALUE);
    return (OSStatus)0;
}

int test_mkdir(const char *path, mode_t mode)
{
    return 0;
}

#define TOSTRING_X(x) #x
#define TOSTRING(x) TOSTRING_X(x)
#define RUN_TEST(result, msg)                                                                                                              \
    TEST_FUNC(buffer, sizeof(buffer), "test-osx");                                                                                         \
    CHECK_RESULT(result, msg)

#define CHECK_RESULT(result, msg)                                                                                                          \
    if (strcmp(buffer, result) != 0)                                                                                                       \
    {                                                                                                                                      \
        printf("FAIL: %s:%d " TOSTRING(TEST_FUNC) "() returned the wrong value.\n"                                                         \
                                                  "Expected: %s\nGot: %s\n",                                                               \
            __FILE__, __LINE__, result, buffer);                                                                                           \
        return 1;                                                                                                                          \
    }                                                                                                                                      \
    else                                                                                                                                   \
    {                                                                                                                                      \
        printf("PASS: " TOSTRING(TEST_FUNC) "() " msg "\n");                                                                               \
    }

int main(int argc, char *argv[])
{
    char buffer[MAX_PATH];

    /*
     * get_user_config_file()
     */

#define TEST_RESULT HOME_VALUE "test-osx.conf"
#define TEST_FUNC get_user_config_file

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    TEST_FUNC(buffer, 5, "test-osx");
    CHECK_RESULT("", "returns empty string when buffer is too small.");

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    RUN_TEST(TEST_RESULT, "works with $XDG_CONFIG_HOME.");

    test_env_xdg_valid = 0;
    test_env_home_valid = 1;
    RUN_TEST(TEST_RESULT, "works with $HOME and not $XDG_CONFIG_HOME.");

    test_env_xdg_valid = 0;
    test_env_home_valid = 0;
    RUN_TEST("", "returns empty string when $XDG_CONFIG_HOME and $HOME are absent.");

#undef TEST_FUNC
#undef TEST_RESULT

    /*
     * get_user_config_folder()
     */

#define TEST_RESULT "/home/test/.config/test-osx/"
#define TEST_FUNC get_user_config_folder

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    TEST_FUNC(buffer, 5, "test-osx");
    CHECK_RESULT("", "returns empty string when buffer is too small.");

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    RUN_TEST(TEST_RESULT, "works with $XDG_CONFIG_HOME.");

    test_env_xdg_valid = 0;
    test_env_home_valid = 1;
    RUN_TEST(TEST_RESULT, "works with $HOME and not $XDG_CONFIG_HOME.");

    test_env_xdg_valid = 0;
    test_env_home_valid = 0;
    RUN_TEST("", "returns empty string when $XDG_CONFIG_HOME and $HOME are absent.");

#undef TEST_FUNC
#undef TEST_RESULT

    /*
     * get_user_data_folder()
     */

#define TEST_RESULT "/home/test/.local/share/test-osx/"
#define TEST_FUNC get_user_data_folder

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    TEST_FUNC(buffer, 5, "test-osx");
    CHECK_RESULT("", "returns empty string when buffer is too small.");

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    RUN_TEST(TEST_RESULT, "works with $XDG_CONFIG_HOME.");

    test_env_xdg_valid = 0;
    test_env_home_valid = 1;
    RUN_TEST(TEST_RESULT, "works with $HOME and not $XDG_CONFIG_HOME.");

    test_env_xdg_valid = 0;
    test_env_home_valid = 0;
    RUN_TEST("", "returns empty string when $XDG_CONFIG_HOME and $HOME are absent.");

#undef TEST_FUNC
#undef TEST_RESULT

    /*
     * get_user_cache_folder()
     */

#define TEST_RESULT "/home/test/.cache/test-osx/"
#define TEST_FUNC get_user_cache_folder

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    TEST_FUNC(buffer, 5, "test-osx");
    CHECK_RESULT("", "returns empty string when buffer is too small.");

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    RUN_TEST(TEST_RESULT, "works with $XDG_CONFIG_HOME.");

    test_env_xdg_valid = 0;
    test_env_home_valid = 1;
    RUN_TEST(TEST_RESULT, "works with $HOME and not $XDG_CONFIG_HOME.");

    test_env_xdg_valid = 0;
    test_env_home_valid = 0;
    RUN_TEST("", "returns empty string when $XDG_CONFIG_HOME and $HOME are absent.");

#undef TEST_FUNC
#undef TEST_RESULT

    printf("All tests passed for platform: OS X.\n");
    return 0;
}

#endif