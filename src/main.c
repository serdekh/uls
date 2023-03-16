#include "../inc/uls.h"

/*
 * TODO: Implement separating files and dir/files from each other
 * TODO: Implement -l flag
 * TODO: Implement poliflags input (-a -l)
 * TODO: Impelement '| cat -e' setting
*/

int main(int argc, char *argv[]) {
    if (argc == 1) mx_uls_no_params();
    
    if (argc == 2) {
        t_list *entries = mx_get_dirent_structures(CURRENT_DIRECTORY);

        if (mx_strcmp(argv[1], FLAG__HIDDEN_FILES_PRINTED) == 0) {
            mx_print_files_and_directories(entries, true);
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
