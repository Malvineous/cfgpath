#include "cfgpath.h"

#include <stdio.h>

int main() {
    char* config_file = malloc(MAX_PATH * sizeof(char));
    char* config_folder = malloc(MAX_PATH * sizeof(char));
    char* data_folder = malloc(MAX_PATH * sizeof(char));
    char* cache_folder = malloc(MAX_PATH * sizeof(char));
    char* too_small = malloc(10 * sizeof(char));

    get_user_config_file(config_file, MAX_PATH, "myapp");
    get_user_config_folder(config_folder, MAX_PATH, "myapp");
    get_user_data_folder(data_folder, MAX_PATH, "myapp");
    get_user_cache_folder(cache_folder, MAX_PATH, "myapp");
    get_user_config_folder(too_small, 10, "myapp");

    printf("Config file:      %s\n", strlen(config_file) ? config_file : "ERROR");
    printf("Config folder:    %s\n", strlen(config_folder) ? config_folder : "ERROR");
    printf("Data folder:      %s\n", strlen(data_folder) ? data_folder : "ERROR");
    printf("Cache folder:     %s\n", strlen(cache_folder) ? cache_folder : "ERROR");
    printf("Should be error:  %s\n", strlen(too_small) ? too_small : "ERROR");
}
