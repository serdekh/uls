#include "../inc/uls.h"

void print_files_and_directories(bool hidden_are_printed) {
    DIR *dir = NULL;
    t_dirent *entry = NULL;

    try_opendir(&dir, CURRENT_DIRECTORY);

    while ((entry = readdir(dir)) != NULL) {
        if (hidden_are_printed) {
            mx_printstrc(entry->d_name, ' '); 
            mx_printchar(' ');
        }
        if (!mx_is_hidden_file(entry->d_name) && !hidden_are_printed) {
            mx_printstrc(entry->d_name, ' '); 
            mx_printchar(' ');
        }   
    }

    closedir(dir);
}
