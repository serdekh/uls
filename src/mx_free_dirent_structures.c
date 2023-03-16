#include "../inc/uls.h"

void mx_free_dirent_structures(t_list *dirent_structures_list) {
    if (!dirent_structures_list) return;

    for (t_list *i = dirent_structures_list; i != NULL; i = i->next) {
        free(i->data);
    }

    while (dirent_structures_list != NULL) {
        mx_pop_front(&dirent_structures_list);
    }
}
