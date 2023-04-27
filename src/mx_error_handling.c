#include "../inc/uls_error.h"
#include "../inc/libmx/inc/libmx.h"

void mx_check_flag_l_position(int argc, char **argv) {
    for (int i = 2; i < argc; i++) {
        if (mx_strcmp(argv[i], "-l") == 0) {
            mx_printerr(ULS_USAGE);
            exit(EXIT_FAILURE);
        }
    }
}

void mx_print_invalid_option(char **argv) {
    mx_printerr("uls: illegal option -- ");
    mx_printerr(&argv[1][1]); // &argv[1][1] -- a flag without '-' symbol
    mx_printerr("\n");
    mx_printerr(ULS_USAGE);
    exit(EXIT_FAILURE);
}
