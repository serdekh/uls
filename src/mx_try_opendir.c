#include "../inc/uls.h"
#include "../inc/uls_error.h"

void mx_try_opendir(DIR **dir, const char *name) {
    if (!name) return;

    *dir = opendir(name);

    if (!(*dir)) {
        char *error = strerror(errno);
        mx_printerr("uls: ");
        mx_printerr(name);
        mx_printerr(": ");
        mx_printerr(error);
        exit(FAILURE);
    }
}
