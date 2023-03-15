#include "../inc/uls.h"

/*
 * TODO: find out how to sort files and directories, 
 * how to implement -l flag and learn functions
 * for it
*/

int main(int argc, char *argv[]) {
    if (argc == 1) {
        t_list *entries = mx_get_dirent_structures(CURRENT_DIRECTORY);

        mx_sort_dirent_structures(entries);
        mx_print_files_and_directories(entries, false);
        mx_free_dirent_structures(entries);

        return 0;
    }

    if (argc == 2) {
        t_list *entries = mx_get_dirent_structures(CURRENT_DIRECTORY);

        if (mx_strcmp(argv[1], FLAG__HIDDEN_FILES_PRINTED) == 0) {
            mx_print_files_and_directories(entries, true);
            return 0;
        }
    }
    
    return 0;
}
