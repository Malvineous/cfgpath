#include "cfgpath.h"

#include <stdio.h>

int main() {
    char config_folder[MAX_PATH];
    char config_file[MAX_PATH];
    char data_folder[MAX_PATH];
    char cache_folder[MAX_PATH];

    get_user_config_folder(config_folder, MAX_PATH, "myapp");
    get_user_config_file(config_file, MAX_PATH, "myapp");
    get_user_data_folder(data_folder, MAX_PATH, "myapp");
    get_user_cache_folder(cache_folder, MAX_PATH, "myapp");

    printf("Config folder: %s\n", strlen(config_folder) ? config_folder : "ERROR");
    printf("Config file:   %s\n", strlen(config_file) ? config_file : "ERROR");
    printf("Data folder:   %s\n", strlen(data_folder) ? data_folder : "ERROR");
    printf("Cache folder:  %s\n", strlen(cache_folder) ? cache_folder : "ERROR");
}
