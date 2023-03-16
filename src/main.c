#include "../inc/uls.h"

/*
 * (1) TODO: Implement separating flags and dir/files from each other
 * (2) TODO: Implement -l flag
 * (3) TODO: Implement poliflags input (-a -l)
 * (4) TODO: Improve Makefile
 * (5) TODO: Impelement '| cat -e' setting
*/

int main(int argc, char *argv[]) {
    if (argc == 1) mx_uls_no_params();

    // temporary block to test mx_get_flags function
    t_list *flags = mx_get_flags(argc, argv);

    mx_free_flags(flags);
    
    if (argc == 2) {
        t_list *entries = mx_get_dirent_structures(CURRENT_DIRECTORY);

        if (mx_strcmp(argv[1], FLAG__HIDDEN_FILES_PRINTED) == 0) {
            mx_sort_dirent_structures(entries);
            mx_print_files_and_directories(entries, true);
            mx_free_dirent_structures(entries);
            return 0;
        }
        else {
            mx_printstr("uls: illegal option -- ");
            mx_printstr(&argv[1][1]);
            mx_printstr("\nusage: uls [-l] [file ...]\n");
            mx_free_dirent_structures(entries);
        }
    }
    
    return 0;
}
