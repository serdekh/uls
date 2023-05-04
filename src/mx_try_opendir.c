#include "../inc/uls.h"
#include "../inc/uls_error.h"

void mx_try_opendir(DIR **dir, const char *name, bool exit_program) {
    if (!name) return;

    *dir = opendir(name);

    if (*dir != NULL) return;

    char *error = strerror(errno);
    mx_printerr("uls: ");
    mx_printerr(name);
    mx_printerr(": ");
    mx_printerr(error);
    if (exit_program) exit(EXIT_FAILURE);
}
