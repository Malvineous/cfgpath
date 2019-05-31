/**
 * @file  cfgpath.core.h
 * @brief Cross platform methods for obtaining paths to configuration files.
 *
 * Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>
 * Copyright (C) 2019 LonghronShen <LonghronShen@hotmail.com>
 *
 * This code is placed in the public domain.  You are free to use it for any
 * purpose.  If you add new platform support, please contribute a patch!
 */

#ifndef CFGPATH_CORE_H
#define CFGPATH_CORE_H

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif
#endif

// The cfgpath library version in the form major * 10000 + minor * 100 + patch.
#define CFGPATH_VERSION 10000

# if defined(CFGPATH_HEADER_ONLY)
#  if defined(CFGPATH_IMPL)
#   define CFGPATH_FUNC
#  else
#   define CFGPATH_FUNC static inline
#  endif
#  if defined(_WIN32) || defined(WIN32) || defined(WIN64)
#   include <cfgpath/detail/cfgpath.impl.win32.h>
#  else
#   include <cfgpath/detail/polyfills/shlobj.polyfills.h>
#   if defined(__linux__)
#    include <cfgpath/detail/cfgpath.impl.linux.h>
#   elif defined(__APPLE__)
#    include <cfgpath/detail/cfgpath.impl.osx.h>
#   else
#    error cfgpath.h functions have not been implemented for your platform!  Please send patches.
#   endif
#  endif
# else
#  include <cfgpath/cfgpath.incl.h>
# endif

#include <cfgpath/detail/polyfills/path_length.polyfills.h>

#endif
