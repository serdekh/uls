#include "../inc/uls.h"

bool mx_is_flag(const char *s) {
    if (!s) return false;

    return (s[0] == '-');
}

t_list *mx_get_dirents(int argc, char **argv) {
    t_list *dirent_structures = NULL;

    for (int i = 1; i < argc; i++) {
        //needs to create another function that will get a dirent struct by a name
        dirent_structures = mx_get_dirent_structures(argv[i]);

        mx_printstr(argv[i]);
        mx_printstr(":\n");

        for (t_list *j = dirent_structures; j != NULL; j = j->next) {
            t_dirent *temp = (t_dirent *)(j->data);

            if (!mx_is_hidden_file(temp->d_name)) {
                mx_printstrc(((t_dirent *)(j->data))->d_name, '\n');
            }
        }

        if (i != argc - 1) {
            mx_printchar('\n');
        }

        mx_free_dirent_structures(dirent_structures);
    }

    return NULL;
}

void mx_check_l_flag(int argc, char *argv[]) {
    if (!argv) return;

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

    mx_get_dirents(argc, argv);

    exit(SUCCESS);
}

void mx_uls_with_params(int argc, char *argv[]) {
    //FIXME: need to check what input we get

    mx_check_l_flag(argc, argv);

    t_list *dirent_structures = mx_get_dirent_structures(CURRENT_DIRECTORY);

    mx_handle_l_flag(dirent_structures);
}
