#include "../inc/uls.h"

void try_opendir(DIR **dir, const char *name) {
    if (!name) return;

    *dir = opendir(name);

    if (!(*dir)) {
        perror(strerror(errno));
        exit(1);
    }
}
