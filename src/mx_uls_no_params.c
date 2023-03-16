#include "../inc/uls.h"

void mx_uls_no_params() {
    t_list *entries = mx_get_dirent_structures(CURRENT_DIRECTORY);

    mx_sort_dirent_structures(entries);
    mx_print_files_and_directories(entries, false);
    mx_free_dirent_structures(entries);

    exit(0);
}
