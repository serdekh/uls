#include "../inc/uls.h"
#include "../inc/uls_error.h"
#include "../inc/libmx/inc/libmx.h"

bool mx_check_flag_l_position(int argc, char **argv) {
    bool result = false;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') continue;

        if (argv[i][1] == 'l') { 
            result = true;
            continue;
        }
        
        mx_print_invalid_option(argv[i]);
        mx_printerr(ULS_USAGE);
        exit(EXIT_FAILURE);
    }

    return result;
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
    mx_printchar('\n');
    if (exit_program) exit(EXIT_FAILURE);
}

void mx_set_error_and_print(int errno_value, char *file, bool exit_program) {
    if (!file) return;
    
    errno = errno_value;
    mx_printerr("uls: ");
    mx_printerr(file);
    mx_printerr(": ");
    mx_printerr(strerror(errno));
    mx_printchar('\n');
    if (exit_program) exit(EXIT_FAILURE);
}
