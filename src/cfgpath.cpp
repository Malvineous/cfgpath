/**
 * @file  cfgpath.cpp
 * @brief Cross platform methods for obtaining paths to configuration files.
 *
 * Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>
 * Copyright (C) 2019 LonghronShen <LonghronShen@hotmail.com>
 *
 * This code is placed in the public domain.  You are free to use it for any
 * purpose.  If you add new platform support, please contribute a patch!
 */

#if defined(CFGPATH_HEADER_ONLY)
#undef CFGPATH_HEADER_ONLY
#endif

#include <cfgpath/cfgpath.h>

#include <exception>
#include <stdexcept>

using namespace std;

template <typename cfgpath_callback>
std::string inline call_function(const string &appname,
                                 cfgpath_callback callback) {
  char path[MAX_PATH];
  callback(path, sizeof(path), appname.c_str());
  if (path[0] == 0) {
    return "";
  }
  return path;
}

std::string
libcfgpath::cfgpath::get_folder_path(libcfgpath::known_spefial_folder folder,
                                     const std::string &appname) {
  switch (folder) {
  case libcfgpath::known_spefial_folder::CONFIG:
    return std::move(call_function(appname, get_user_config_folder));
  case libcfgpath::known_spefial_folder::DATA:
    return std::move(call_function(appname, get_user_data_folder));
  case libcfgpath::known_spefial_folder::CACHE:
    return std::move(call_function(appname, get_user_cache_folder));
  default:
    throw std::runtime_error("Unkown special folder type given.");
  }
}

std::string
libcfgpath::cfgpath::get_file_path(libcfgpath::known_spefial_folder folder,
                                   const std::string &appname,
                                   const std::string &fileName) {
  switch (folder) {
  case libcfgpath::known_spefial_folder::CONFIG:
    return std::move(call_function(appname, get_user_config_folder));
  case libcfgpath::known_spefial_folder::DATA:
  case libcfgpath::known_spefial_folder::CACHE:
  default:
    return libcfgpath::cfgpath::get_folder_path(folder, appname) + fileName;
  }
}
