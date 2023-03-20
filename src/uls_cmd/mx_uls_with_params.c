#include "../../inc/uls.h"

void mx_check_l_flag(char *argv[]) {
    if (!argv) return;

    bool flag_l_found = mx_strcmp(argv[1], "-l") == 0;

    if (flag_l_found) {
        return;
    }
    if (!flag_l_found) {
        write(2, ULS_USAGE, strlen(ULS_USAGE));
        exit(0);
    }
}

void mx_uls_with_params(int argc, char *argv[]) {
    if (argc) {}
    //FIXME: need to check what input we get

    mx_check_l_flag(argv);

    t_list *dirent_structures = mx_get_dirent_structures(CURRENT_DIRECTORY);

    mx_handle_l_flag(dirent_structures);
}
