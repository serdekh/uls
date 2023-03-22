#include "../inc/uls.h"
#include "../inc/uls_error.h"

void mx_check_l_flag(int argc, char **argv) {
    if (!argv || argc <= 0) return;

    mx_check_flag_l_position(argc, argv);

    bool flag_l_found = mx_strcmp(argv[1], "-l") == 0;

    if (flag_l_found) {
        return;
    }

    bool invalid_flag = (mx_is_flag(argv[1]) && argv[1][0] != 'l');

    if (invalid_flag) {
        mx_print_invalid_option(argv);
    }

    mx_print_dirents(argc, argv);

    exit(SUCCESS);
}

void mx_handle_l_flag(t_list *dirent_structures) {
    if (!dirent_structures) return;

    t_list *files = NULL;
    //t_list *folders = NULL;

    for (t_list *t = dirent_structures; t != NULL; t = t->next) {
        t_dirent *temp = (t_dirent *)(t->data);

        if (!mx_is_hidden_file(temp->d_name)) {
            t_detailed_information *info = (t_detailed_information *)malloc(sizeof(t_detailed_information));

            mx_set_detailed_info(temp->d_name, info);
            mx_push_back(&files, info);
        }

        // if (!mx_is_hidden_file(temp->d_name) && temp->d_type == DT_DIR) {
        //     t_dirent *folder = (t_dirent *)malloc(sizeof(t_dirent));
        //     mx_direntcpy(folder, temp);
        //     mx_push_back(&folders, folder);
        // }
    }

    mx_free_dirent_structures(dirent_structures);

    mx_print_total(files);
    mx_sort_detailed_infos(files);
    mx_print_detailed_infos(files);
    mx_free_detailed_infos(files);

    // mx_sort_dirent_structures(folders);

    // for (t_list *i = folders; i != NULL; i = i->next) {
    //     mx_print_dirent_structures_in_folder((t_dirent *)(i->data));
    // }

    // mx_free_dirent_structures(folders);

    exit(SUCCESS);
}
