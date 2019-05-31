/**
 * @file  cfgpath.incl.h
 * @brief Cross platform methods for obtaining paths to configuration files.
 *
 * Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>
 * Copyright (C) 2019 LonghronShen <LonghronShen@hotmail.com>
 *
 * This code is placed in the public domain.  You are free to use it for any
 * purpose.  If you add new platform support, please contribute a patch!
 * 
 * Example use:
 *
 * char cfgdir[256];
 * get_user_config_file(cfgdir, sizeof(cfgdir), "myapp");
 * if (cfgdir[0] == 0) {
 *     printf("Unable to find home directory.\n");
 *     return 1;
 * }
 * printf("Saving configuration file to %s\n", cfgdir);
 *
 * A number of constants are also defined:
 *
 *  - MAX_PATH: Maximum length of a path, in characters.  Used to allocate a
 *      char array large enough to hold the returned path.
 *
 *  - PATH_SEPARATOR_CHAR: The separator between folders.  This will be either a
 *      forward slash or a backslash depending on the platform.  This is a
 *      character constant.
 *
 *  - PATH_SEPARATOR_STRING: The same as PATH_SEPARATOR_CHAR but as a C string,
 *      to make it easier to append to other string constants.
 */

#ifndef CFGPATH_H
#define CFGPATH_H

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif
#endif

#include <cfgpath/cfgpath.core.h>

#ifdef __cplusplus

#include <string>

namespace libcfgpath {

enum known_spefial_folder {
  CONFIG,
  DATA,
  CACHE,
};

class cfgpath {
public:
  static std::string get_folder_path(libcfgpath::known_spefial_folder folder,
                                     const std::string &appname);

  static std::string get_file_path(libcfgpath::known_spefial_folder folder,
                                   const std::string &appname,
                                   const std::string &fileName);
};

} // namespace libcfgpath

#endif

#endif