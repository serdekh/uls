#include "../inc/uls.h"
#include "../inc/utils.h"
#include "../inc/uls_error.h"
#include "../inc/libmx/inc/libmx.h"

bool mx_check_flag_l_position(int argc, char **argv) {
    if (argc){}

    if (argv[1][0] == '-' && mx_strcmp(argv[1], "-l") != 0) {
        mx_print_invalid_option(argv[1]);
        mx_printerr(ULS_USAGE);
        exit(EXIT_FAILURE);
    }

    return true;
}

void mx_print_invalid_option(char *flag) {
    mx_printerr("uls: illegal option -- ");
    #ifdef __APPLE__
    mx_printerrn(&flag[1], 1);
    #endif
    #ifdef __linux__
    mx_printerr(&flag[1]);
    #endif
    mx_printerr("\n");
    mx_printerr(ULS_USAGE);
    exit(EXIT_FAILURE);
}

void mx_print_no_such_file_or_directory(char *file, bool exit_program) {
    if (!file) return;
    
    errno = ENOENT;
    mx_printerr("uls: ");
    mx_printerr(file);
    mx_printerr(": ");
    mx_printerr(strerror(errno));
    mx_printerr("\n");
    if (exit_program) exit(EXIT_FAILURE);
}

void mx_set_error_and_print(int errno_value, char *file, bool exit_program, bool newline) {
    if (!file) return;
    
    errno = errno_value;
    mx_printerr("uls: ");
    mx_printerr(file);
    mx_printerr(": ");
    mx_printerr(strerror(errno));
    if (newline) mx_newline();
    if (exit_program) exit(EXIT_FAILURE);
}
