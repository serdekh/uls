#include "../inc/uls.h"

void mx_free_flags(t_list *flags) {
    if (!flags) return;

    for (t_list *i = flags; i != NULL; i = i->next) {
        mx_printstrc((char *)(i->data), '\n');
        free(i->data);
    }

    while (flags != NULL) {
        mx_pop_front(&flags);
    }
}
