#include "../inc/uls.h"
#include "../inc/utils.h"

/*
 * (0) TODO: Implement table printing in without -l case
 * 
 * (1) DONE (MAYBE): Implement separating flags and dir/files from each other
 *           By printing firstly the files and the contains of dirs
 * (2) DONE: Implement -l flag
 * (3) DONE: Improve Makefile
 * (4) DONE (MAYBE, REQUIRES SOME TESTS): Impelement '| cat -e' setting
*/

int main(int argc, char *argv[]) {
    if (argc == 1 && isatty(STDOUT_FILENO) == 0) mx_call_uls_cat_e();
    if (argc == 1) mx_call_uls_without_params(CURRENT_DIRECTORY, true);
    if (argc >= 2) mx_call_uls_with_params(argc, argv);

    return 0;
}
