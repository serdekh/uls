#include "../inc/uls.h"
#include "../inc/uls_error.h"

void mx_call_uls_without_params(char *path) {
    if (!path) path = CURRENT_DIRECTORY;
    
    t_list *entries = mx_get_dirent_structures(path);

    mx_sort_dirent_structures(entries);
    mx_print_files_and_directories(entries);
    mx_free_dirent_structures(entries);

    exit(EXIT_SUCCESS);
}

void mx_call_uls_l() {
    t_list *dirent_structures = mx_get_dirent_structures(CURRENT_DIRECTORY);
    t_list *detailed_infos = mx_parse_dirents_to_detailed_infos(dirent_structures);

    mx_sort_detailed_infos(detailed_infos);
    mx_print_detailed_infos(detailed_infos);
    mx_free_detailed_infos(detailed_infos);
    mx_free_dirent_structures(dirent_structures);

    exit(EXIT_SUCCESS);
}

void mx_call_uls_with_params(int argc, char **argv) {
    mx_check_l_flag(argc, argv);

    if (argc == 2) mx_call_uls_l();

    t_list *argv_dirent_structures = NULL;

    for (int i = 2; i < argc; i++) {
        t_dirent *dirent = mx_get_dirent_structure(argv[i]);

        if (dirent != NULL) {
            mx_push_back(&argv_dirent_structures, dirent);
            continue;
        }

        mx_print_no_such_file_or_directory(argv[i]);

        mx_free_dirent_structures(argv_dirent_structures);

        exit(EXIT_FAILURE);
    }

    mx_handle_l_flag(argv_dirent_structures);
}
