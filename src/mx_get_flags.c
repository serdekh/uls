#include "../inc/uls.h"

t_list *mx_get_flags(int argc, char **argv) {
    if (!argv || argc <= 0) return NULL;

    t_list *flags = NULL;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            char *str = mx_strnew(strlen(argv[i]));
            mx_strcpy(str, argv[i]);
            mx_push_back(&flags, str);
        }
    }

    return flags;
}
