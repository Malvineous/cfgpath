/**
 * @file  test-linux.c
 * @brief cfgpath.h test code for the Linux platform.
 *
 * Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>
 * Copyright (C) 2019 LonghronShen <LonghronShen@hotmail.com>
 *
 * This code is placed in the public domain.  You are free to use it for any
 * purpose.  If you add new platform support, please contribute a patch!
 */

#ifdef __linux__

#undef WIN32
#undef _WIN32
#undef __APPLE__

#include <string.h>
#include <stdio.h>

#define CFGPATH_HEADER_ONLY

#define getenv test_getenv
#define mkdir test_mkdir

#include <cfgpath/cfgpath.h>

#define XDG_CONFIG_HOME_VALUE "/home/test/.config"
#define HOME_VALUE "/home/test"

int test_env_xdg_valid;  /* Does $XDG_CONFIG_HOME exist? */
int test_env_home_valid; /* Does $HOME exist? */

char getenv_buffer[256];

char *test_getenv(const char *var)
{
    if (test_env_xdg_valid && (strcmp(var, "XDG_CONFIG_HOME") == 0))
    {
        strcpy(getenv_buffer, XDG_CONFIG_HOME_VALUE);
        return getenv_buffer;
    }
    if (test_env_home_valid && (strcmp(var, "HOME") == 0))
    {
        strcpy(getenv_buffer, HOME_VALUE);
        return getenv_buffer;
    }
    return NULL;
}

int test_mkdir(const char *path, mode_t mode)
{
    return 0;
}

#define TOSTRING_X(x) #x
#define TOSTRING(x) TOSTRING_X(x)
#define RUN_TEST(result, msg)                                                                                                              \
    TEST_FUNC(buffer, sizeof(buffer), "test-linux");                                                                                       \
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
    char buffer[256];

    /*
     * get_user_config_file()
     */

#define TEST_RESULT "/home/test/.config/test-linux.conf"
#define TEST_FUNC get_user_config_file

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    TEST_FUNC(buffer, 5, "test-linux");
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

#define TEST_RESULT "/home/test/.config/test-linux/"
#define TEST_FUNC get_user_config_folder

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    TEST_FUNC(buffer, 5, "test-linux");
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

#define TEST_RESULT "/home/test/.local/share/test-linux/"
#define TEST_FUNC get_user_data_folder

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    TEST_FUNC(buffer, 5, "test-linux");
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

#define TEST_RESULT "/home/test/.cache/test-linux/"
#define TEST_FUNC get_user_cache_folder

    test_env_xdg_valid = 1;
    test_env_home_valid = 1;
    TEST_FUNC(buffer, 5, "test-linux");
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

    printf("All tests passed for platform: Linux.\n");
    return 0;
}

#endif