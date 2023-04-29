#include "../inc/uls.h"

/*
 * (3) TODO: Improve Makefile
 * (4) TODO: Impelement '| cat -e' setting
 * 
 * (1) DONE (MAYBE): Implement separating flags and dir/files from each other
 *           By printing firstly the files and the contains of dirs
 * (2) DONE: Implement -l flag
*/

int main(int argc, char *argv[]) {
    // struct winsize w;
    // ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // printf ("lines %d\n", w.ws_row);
    // printf ("columns %d\n", w.ws_col);
    
    if (argc == 1 && isatty(STDOUT_FILENO) == 0) mx_call_uls_cat_e();
    if (argc == 1) mx_call_uls_without_params(CURRENT_DIRECTORY);
    if (argc >= 2) mx_call_uls_with_params(argc, argv);
    return 0;
}
