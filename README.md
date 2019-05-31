cfgpath.h: Cross platform methods for obtaining paths to configuration files
============================================================================

Copyright (C) 2013 Adam Nielsen <malvineous@shikadi.net>

Copyright (C) 2019 LonghronShen <LonghronShen@hotmail.com>

---

This is a simple header file that provides a handful of functions to obtain
paths to configuration files, regardless of the operating system the
application is running under.

It requires no dependencies beyond each platform's standard API.

This code is placed in the public domain.  You are free to use it for any
purpose.  If you add new platform support, please contribute a patch!

Basic use:

```C

#include <cfgpath/cfgpath.h>

char cfgdir[MAX_PATH];
get_user_config_file(cfgdir, sizeof(cfgdir), "myapp");
if (cfgdir[0] == 0)
{
  printf("Unable to find home directory.\n");
  return 1;
}
printf("Saving configuration file to %s\n", cfgdir);

```
If you are using C++, you can also use it like this:

```C++

#include <exception>
#include <cfgpath/cfgpath.h>

auto config_folder_path = libcfgpath::cfgpath::get_folder_path(libcfgpath::known_spefial_folder::CONFIG, "myapp");

if (config_folder_path == "")
{
 throw std::exception("Unable to find config directory.");
}

```

To integrate it into your own project, just copy cfgpath.h.
Or clone the project as a submodule of your project, then use **add_subdirectory** to add the subfolder as an externl dependency.

All the other files are for testing to make sure it works correctly, so you don't need them unless you intend to make changes and send me a patch.

Supported platforms are currently:

* Linux
* Mac OS X
* Windows

Patches adding support for more platforms would be greatly appreciated.
