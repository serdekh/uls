#include "../inc/uls.h"
#include "../inc/uls_error.h"
#include "../inc/uls_foreach.h"

void mx_call_uls_cat_e() {
    t_list *dirents = mx_dirents_get(CURRENT_DIRECTORY);

    if (!dirents) return;

    mx_dirents_sort(dirents);
    mx_foreach_t_dirent(dirents, mx_t_dirent_print_name_newline);
    mx_dirents_free(dirents);

    exit(EXIT_SUCCESS);
}

void mx_call_uls_without_params(char *path, bool exit_program) {
    if (!path) path = CURRENT_DIRECTORY;
    
    t_list *entries = mx_dirents_get(path);

    mx_dirents_sort(entries);
    mx_dirents_print_both(entries);
    mx_dirents_free(entries);

    mx_printchar('\n');

    if (exit_program) exit(EXIT_SUCCESS);
}

void mx_call_uls_l() {
    t_list *dirents = mx_dirents_get(CURRENT_DIRECTORY);
    t_list *dirent_infos = mx_dirents_parse_to_dirent_infos(dirents);

    mx_print_total(dirent_infos);
    mx_dirent_infos_sort(dirent_infos);
    mx_dirent_infos_print(dirent_infos);
    mx_dirent_infos_free(dirent_infos);
    mx_dirents_free(dirents);

    exit(EXIT_SUCCESS);
}

void mx_validate_args(int argc, char **argv) {
    
    if (mx_strcmp(argv[1], "-l") == 0) return;

    if (argv[1][0] == '-' && mx_strcmp(argv[1], "-l")) {
        mx_print_invalid_option(argv[1]);
        exit(EXIT_FAILURE);
    }

    mx_dirents_print(argc, argv);

    exit(EXIT_SUCCESS);
}

void mx_call_uls_with_params(int argc, char **argv) {
    //mx_check_l_flag(argc, argv);
    mx_validate_args(argc, argv);
    if (argc == 2) mx_call_uls_l();

    t_list *main_input_dirents = NULL;

    for (int i = 2; i < argc; i++) {
        t_dirent *dirent = mx_dirent_get(argv[i]);

        if (dirent == NULL) {
            mx_print_no_such_file_or_directory(argv[i], false);
            continue; 
        }
        mx_push_back(&main_input_dirents, dirent);  
    }

    mx_dirents_sort(main_input_dirents);
    mx_handle_l_flag(main_input_dirents, argc);
}
