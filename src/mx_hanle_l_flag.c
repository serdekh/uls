#include "../inc/uls.h"

void mx_handle_l_flag(t_list *dirent_structures) {
    if (!dirent_structures) return;

    t_list *detailed_infos = NULL;

    for (t_list *t = dirent_structures; t != NULL; t = t->next) {
        t_dirent *temp = (t_dirent *)(t->data);

        if (!mx_is_hidden_file(temp->d_name)) {
            t_detailed_information *info = (t_detailed_information *)malloc(sizeof(t_detailed_information));

            mx_set_detailed_info(temp->d_name, info);
            mx_push_back(&detailed_infos, info);
        }
    }

    mx_print_total(detailed_infos);
    mx_sort_detailed_infos(detailed_infos);
    mx_print_detailed_infos(detailed_infos);
    mx_free_detailed_infos(detailed_infos);
    mx_free_dirent_structures(dirent_structures);

    exit(SUCCESS);
}
