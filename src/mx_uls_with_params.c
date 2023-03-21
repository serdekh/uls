#include "../inc/uls.h"

bool mx_is_flag(const char *s) {
    if (!s) return false;

    return (s[0] == '-');
}

// FIXME: try to find the way how to print data inside a dir
void mx_print_dirents(int argc, char **argv) {
    if (!argv || argc <= 0) return;

    t_list *dirent_structures = NULL;

    for (int i = 1; i < argc; i++) {
        t_dirent *dirent = mx_get_dirent_structure(argv[i]);

        if (dirent != NULL) {
            mx_push_back(&dirent_structures, dirent);
        }
    }

    for (t_list *i = dirent_structures; i != NULL; i = i->next) {
        t_dirent *temp = (t_dirent *)(i->data);

        if (temp->d_type == DT_REG && !mx_is_hidden_file(temp->d_name)) {
            mx_printstrc(temp->d_name, ' ');
        }
    }

    mx_printchar('\n');

    for (t_list *i = dirent_structures; i != NULL; i = i->next) {
        t_dirent *temp = (t_dirent *)(i->data);

        if (temp->d_type == DT_DIR && !mx_is_hidden_file(temp->d_name)) {
            mx_printchar('\n');
            mx_printstrc(temp->d_name, ':');
            mx_printchar('\n');

            t_list *dirent_structures_in_folder = mx_get_dirent_structures(temp->d_name);

            mx_sort_dirent_structures(dirent_structures_in_folder);

            for (t_list *j = dirent_structures_in_folder; j != NULL; j = j->next) {
                t_dirent *temp = (t_dirent *)(j->data);

                if (!mx_is_hidden_file(temp->d_name)) {
                    mx_printstrc(temp->d_name, '\n');
                }
            }

            mx_free_dirent_structures(dirent_structures_in_folder);
        }
    }

    mx_free_dirent_structures(dirent_structures);
}

void mx_check_l_flag(int argc, char **argv) {
    if (!argv) return;

    for (int i = 2; i < argc; i++) {
        if (mx_strcmp(argv[i], "-l") == 0) {
            mx_printerr(ULS_USAGE);
            exit(FAILURE);
        }
    }

    bool flag_l_found = mx_strcmp(argv[1], "-l") == 0;
    bool invalid_flag = (mx_is_flag(argv[1]) && argv[1][0] != 'l');

    if (flag_l_found) {
        return;
    }
    if (invalid_flag) {
        mx_printerr("uls: illegal option -- ");
        mx_printerr(&argv[1][1]); // &argv[1][1] -- a flag without '-' symbol
        mx_printerr("\n");
        mx_printerr(ULS_USAGE);
        exit(FAILURE);
    }

    mx_print_dirents(argc, argv);

    exit(SUCCESS);
}

void mx_uls_with_params(int argc, char **argv) {
    //FIXME: need to check what input we get

    mx_check_l_flag(argc, argv);

    //FIXME: implement checking: either there are files and dirs after -l (then print info about them)
    //       or use default setting 
    t_list *dirent_structures = mx_get_dirent_structures(CURRENT_DIRECTORY);

    mx_handle_l_flag(dirent_structures);
}
