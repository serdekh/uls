#include "../inc/uls.h"
#include "../inc/uls_error.h"

void mx_uls_no_params(char *path) {
    if (!path) {
        path = CURRENT_DIRECTORY;
    }

    t_list *entries = mx_get_dirent_structures(path);

    mx_sort_dirent_structures(entries);
    mx_print_files_and_directories(entries);
    mx_free_dirent_structures(entries);

    exit(SUCCESS);
}
