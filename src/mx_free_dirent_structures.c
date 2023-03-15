#include "../inc/uls.h"

void mx_free_dirent_structures(t_list *dirent_structures_list) {
    for (t_list *i = dirent_structures_list; i != NULL; i = i->next) {
        free((t_dirent*)(i->data));
    }

    free(dirent_structures_list);
}
