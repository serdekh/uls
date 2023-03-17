#include "../inc/uls.h"

/*
 * (1) TODO: Implement separating flags and dir/files from each other
 *           By printing firstly the files and the contains of dirs
 * (2) TODO: Implement -l flag
 * (3) TODO: Improve Makefile
 * (4) TODO: Impelement '| cat -e' setting
*/

/*
    PLANNING TO DO: implement separation files and directories
    to print file names and then print files from directories
*/

int main(int argc, char *argv[]) {
    if (argv) {} // to avoid clang error
    
    if (argc == 1) mx_uls_no_params();

    if (argc >= 2) mx_uls_with_params();

    return 0;
}
