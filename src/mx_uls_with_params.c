#include "../inc/uls.h"
#include "../inc/uls_error.h"



void mx_uls_with_params(int argc, char **argv) {
    //FIXME: need to check what input we get

    mx_check_l_flag(argc, argv);

    if (argc == 2) {
        t_list *dirent_structures = mx_get_dirent_structures(CURRENT_DIRECTORY);
        mx_handle_l_flag(dirent_structures);
    }

    t_list *argv_dirent_structures = NULL;

    for (int i = 2; i < argc; i++) {
        t_dirent *dirent = mx_get_dirent_structure(argv[i]);

        if (dirent != NULL) {
            mx_push_back(&argv_dirent_structures, dirent);
        }
    }

    mx_handle_l_flag(argv_dirent_structures);
}
