#include "../inc/uls.h"

/*
 * TODO: find out how to sort files and directories, 
 * how to implement -l flag and learn functions
 * for it
*/

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_files_and_directories(false);
        return 0;
    }

    if (argc == 2) {
        if (mx_strcmp(argv[1], FLAG__HIDDEN_FILES_PRINTED) == 0) {
            print_files_and_directories(true);
            return 0;
        }
    }
    
    return 0;
}
