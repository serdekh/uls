#include "../inc/uls.h"

/*
 * (1) TODO: Implement separating flags and dir/files from each other
 *           By printing firstly the files and the contains of dirs
 * (3) TODO: Improve Makefile
 * (4) TODO: Impelement '| cat -e' setting
 * 
 * (2) DONE: Implement -l flag
*/

/*
    PLANNING TO DO: implement separation files and directories
    to print file names and then print files from directories
*/

int main(int argc, char *argv[]) {
    if (argc == 1) mx_uls_no_params(CURRENT_DIRECTORY);
    if (argc >= 2) mx_uls_with_params(argc, argv);
    return 0;
}
